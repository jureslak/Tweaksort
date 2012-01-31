#ifndef TWEAKSORT_LEARN_HPP
#define TWEAKSORT_LEARN_HPP

#include "conf.hpp"
#include "sort.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <time.h>


#define INF size_t(-1)

namespace tweaksort
{

/**
 * Returns minimum of two.
 * @param a First value
 * @param b Second value
 * @return Lower of values
 */
template <typename T>
T min(const T a, const T b) {
    return (a < b) ? a : b;
}

/** 
 * Fills target container with random elements from first container.
 * @param target Container to be filled.
 * @param data Container form which elements are taken.
 * @param n Size of target container.
 */
template <typename container_t>
void random_fill(container_t& target, const container_t& data, const size_t n) {
    // include mersenne twister sometime, default rand() sucks.
    target.resize(n);
    for (typename container_t::iterator i = target.begin(); i < target.end(); ++i) {
        *i = data[rand()%data.size()];
    }
}

/**
 * Object helping at comparison of two sorts.
 */
template <typename container_t>
struct Compare {
  public:
    const size_t iterations, limit;
    const double acceleration;
    const container_t data;

    /**
     * Constructor.
     * @param _iterations Numeber of iterationsto be made for each length.
     * @param _limit Number of elements to be hold in memory.
     * @param _acceleration How much to increment the jump length each time.
     * @param _data Sample data.
     */
    Compare(const size_t _iterations, const size_t _limit, const double _acceleration, const container_t& _data) :
        iterations(_iterations), limit(_limit), acceleration(_acceleration), data(_data) {
            assert(data.size() > 0);
            assert(int(acceleration) >= 0);
        }

    /**
     * Returns time that sort spent sorting container of length N.
     * @param N Length of container. Limit MUST be greater.
     * @param conf Configuration for the sort routine.
     * @return Time that sort spent sorting one container of length N.
     */
    double time_it(const size_t N, const conf_t& conf) const {
        assert(limit >= N);// assure this is true
        double delta = 0;
        timespec start, end;
        std::vector<container_t> test;
        size_t count = 0, length;
    //    cout << N << ' ' << iterations << ' ' << limit << endl;
    //     std::cout << "in timing" << std::endl;
        while (count < iterations) {
    //        cout << "count: " << count <<endl;
            if (N == 0) { length = iterations - count; }
            else { length = min(limit/N, iterations-count); }

            test.resize(length);
    //         std::cout << "in while, filling" << std::endl;
            size_t i;
            for (i = 0; i < length; ++i) {
                random_fill(test[i], data, N);
            }
    //        std::cout << "filled, i: " << i << ", sorting" << std::endl;
            count += i;

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
            for (size_t i = 0; i < length; ++i) {
                tweaksort::sort(test[i].begin(), test[i].end(), conf);
            }
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            delta += (end.tv_sec - start.tv_sec)*1e9 + (end.tv_nsec - start.tv_nsec);
        }
        return delta / iterations;
    }

    /**
     * Operator that compares tho sorts.
     * @param a First sort's conf.
     * @param b Seconf sort's conf.
     * @return True if first better, false otherwise.
     */
    bool operator()(const conf_t a, const conf_t b, const size_t n) const {
        return time_it(n, a) < time_it(n, b);
    }

    /**
     * Operator that prints the Compare object.
     * @param o Output stream.
     * @param c Compare object to be printed.
     * @return Output stream with Compare object in it.
     */
    template <typename contain_t>
    friend std::ostream& operator<<(std::ostream& o, const Compare<contain_t>& c);
};

template <typename contain_t>
std::ostream& operator<<(std::ostream& o, const Compare<contain_t>& c){
    o << "iter: " << c.iterations << std::endl << "limit: " << c.limit <<
        std::endl << "acc: " <<  c.acceleration;
    return o;
}

/**
 * Returns a compare structure.
 * @param iterations The number of iterations that will be done sorting. The larger, the
 * more exact the measurement. This is a suggestion for the algorithm.
 * @param limit The number of elements algo is allowed to use. The
 * larger, the faster. MUST be at least as large as M
 * @param acceleration Value that tells how much to increment the distance between tested
 * lengths each time. The smaller more exact the measurment. MUST be more than 0.
 * @param data The sample data. The order of the data elements is not important, they will
 * be randomly chosen for each test. This data should match your typical dataset closely,
 * since that will make the bounds better. Testing data structures will
 * be the same as container_t. They must support random indexing and stl datastructure
 * interfaces. The algorithm uses user-supplied containers because container
 * implementation dictates the weights of member access versus member comparison etc. For
 * instance, if your data structure simulates a serial medium (list), mergesort will
 * perform much faster than the rest, since it is more in-order.
 * @return Compare structure.
 */
template <typename container_t>
Compare<container_t> make_compare(const size_t iterations, const size_t limit, const double acceleration, const container_t& data) {
    return Compare<container_t>(iterations, limit, acceleration, data);
}
/** 
 * Finds best sort at N.
 * Simple maximum algorithm.
 * @param n Length of data structure.
 * @param confs Vector of confs, among which best one is chosen.
 * @param cmp Compare structure.
 * @return Best conf of those listet in confs.
 */
template <typename container_t>
conf_t n_best(const size_t n, const std::vector<conf_t>& confs, const Compare<container_t>& cmp) {
    assert(confs.size() > 0);
    conf_t best = confs[0];
    for (size_t i = 1; i < confs.size(); ++i) {
        if (cmp(confs[i], best, n)) { // če je boljši
            best = confs[i];
        }
    }
    return best;
}

/** 
 * Finds intersection point between two sorts between two lengths.
 * Uses bisection algorithm.
 * @param m Lower bound.
 * @param M Upper bound.
 * @param alfa Configuration for first algortihm.
 * @param beta Configuration for second algoritm.
 * @param cmp Compare structure.
 * @return Intersection point between m and M.
 */
template <typename container_t>
size_t intersection(size_t m, size_t M, const conf_t alfa, const conf_t beta, const Compare<container_t>& cmp) {
    bool low, middle, high;
    low = cmp(alfa, beta, m);
    high = cmp(alfa, beta, M);
    // not good what now?
    if (low == high) { return (low) ? M : m; }
    while (M - m > 1) {
        middle = cmp(alfa, beta, (m+M)/2);
        if (middle == low) {
            low = middle;
            m = (m + M) / 2;
        } else {
            high = middle;
            M = (m + M) / 2;
        }
    }
    return m;
}

/**
 * Finds next step when building conf.
 * @param alts Vector of confs, that may represent the next step.
 * @param cmp Compare structure.
 * @param progress Which length are we testing right now. Incremented in function.
 * @param distance Tells how much to increment the progress next time. Incremented in
 * function. Progres is incremented like distance at accelerated motion.
 * @param M Upper bound for learning, if progress is over M, quit.
 * @return Best of alts, with upper limit set.
 */
template <typename container_t>
conf_t find_step(const std::vector<conf_t>& alts, const Compare<container_t>& cmp,
        double& progress, double& distance, const size_t M) {
    progress += distance;
    conf_t old_best = n_best(progress, alts, cmp);
    std::cout << ":::::: progress: " << progress << std::endl;
    std::cout << ":::::: best now: " << old_best << std::endl;

    conf_t new_best;
    do {
        distance += cmp.acceleration;
        progress += distance;
        std::cout << ":::::: progress: " << (progress) << std::endl;
        if (progress > M) {
            std::cout << ":::::: Progress is over M! Finished!" << std::endl;
            old_best.set_last_limit(INF);
            return old_best;
        }
        new_best = n_best(size_t(progress), alts, cmp);
    } while (new_best == old_best);
    progress -= distance;
    std::cout << ":::::: progress: " << (progress) << std::endl;
    std::cout << ":::::: beaten by: " << new_best << std::endl;
    old_best.set_last_limit(intersection(progress, progress + distance, old_best, new_best, cmp));
    return old_best;
}

/**
 * Find the best conf up to given upper bound by testing different configurations with
 * given compare stucture.
 * @param M Upper bound for learning. Up to this legth, the conf is optimal. For legths
 * bigger than M, it may not be. This is the maximal number of elements
 * that sorting will be attempted for. Data is not required to be this long, but it helps.
 * If data is not long enough, duplicate elements will be drawn from it.
 * @param cmp Compare structure.
 * @return Optimal conf up to M.
 */
template <typename container_t>
conf_t learn(const size_t M, const Compare<container_t>& cmp) {
    std::cout << cmp << std::endl;
    std::cout << ":: M :: " << M << std::endl;

    std::vector<conf_t> confs, adds;
    adds.push_back(conf_t('i', INF));
    adds.push_back(conf_t('q', INF));
    adds.push_back(conf_t('h', INF));
    adds.push_back(conf_t('m', INF));
    adds.push_back(conf_t('s', INF));
    confs.resize(adds.size());

    conf_t best;
    double progress = 4, distance = 1;
    do {
        for (size_t i = 0; i < confs.size(); ++i) {
            confs[i] = best + adds[i]; /* making new possibilities */
        }
        best = find_step(confs, cmp, progress, distance,  M);
        std::cout << ":: best :: " << best << std::endl;
    } while(progress < M);
    best.beautify();
    std::cout << ":: final :: " << best << std::endl;
    return best;
}

} // tweaksort
#endif
