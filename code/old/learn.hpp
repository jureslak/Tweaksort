#ifndef TWEAKSORT_LEARN_HPP
#define TWEAKSORT_LEARN_HPP

#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <vector>
#include <cassert>
#include <sys/time.h>

#include "i.hpp"
#include "q.hpp"
#include "h.hpp"
#include "m.hpp"

#define INSERTION 0
#define QUICK 1
#define HEAP 2
#define MERGE 3
#define INF (-1)

#include <iostream>
namespace tweaksort
{

typedef std::vector<std::pair<char, int> > conf_t;

template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

template <typename container_t>
void random_fill(container_t& target, container_t& data, size_t n)
{
    // include mersenne twister sometime, default rand() sucks.
    target.resize(n);
    for (typename container_t::iterator i = target.begin(); i < target.end(); ++i) {
        *i = data[rand()%data.size()];
    }
}


#define timefunc(sort, name) \
template <typename container_t> \
double name(size_t N, size_t iterations, size_t limit, container_t &data)\
{\
    assert(limit >= N);\
    double delta = 0;\
    timeval start, end;\
    std::vector<container_t> test;\
    size_t count = 0, length;\
    /* std::cout << "in timing" << std::endl; */ \
    while (count < iterations) {\
        if (N == 0) { length = iterations - count; } \
        else { length = min(limit/N, iterations-count); }\
        test.resize(length);\
        /* std::cout << "in while, filling" << std::endl;*/\
        size_t i;\
        for (i = 0; i < length; ++i) {\
            random_fill(test[i], data, N);\
        }\
    /*    std::cout << "filled, i: " << i << ", sorting" << std::endl;*/\
        count += i;\
    \
        gettimeofday(&start, NULL);\
        for (size_t i = 0; i < length; ++i) {\
            sort(test[i].begin(), test[i].end());\
        }\
        gettimeofday(&end, NULL);\
        delta += (end.tv_sec - start.tv_sec)*1000000.0 + (end.tv_usec - start.tv_usec);\
    }\
    return delta / iterations;\
}

timefunc(insertion_sort, i_time)
timefunc(quick_sort, q_time)
timefunc(merge_sort, m_time)
timefunc(heap_sort, h_time)

#define intersection_func(sort1, sort2, name) \
template <typename container_t> \
int name(size_t M, size_t iterations, size_t limit, container_t& data) { \
    size_t m = 5;\
    double max_time_sort1 = sort1(M, iterations, limit, data);\
    double max_time_sort2 = sort2(M, iterations, limit, data);\
\
    double max_d = max_time_sort1 - max_time_sort2;\
\
    double t_sort1, t_sort2, t_d;\
    while (M - m > 1) {\
        t_sort1 = sort1((m+M)/2, iterations, limit, data);\
        t_sort2 = sort2((m+M)/2, iterations, limit, data);\
        t_d = t_sort1 - t_sort2; \
        if ((t_d < 0 && max_d < 0) || (t_d > 0 && max_d > 0)) { \
            M = (M+m)/2;\
        } else {\
            m = (M+m)/2;\
        }\
    }\
    return (m == 5) ? INF : ((max_time_sort1 > max_time_sort2) ? m : -m); \
}\

intersection_func(i_time, q_time, i_q_intr)
intersection_func(i_time, h_time, i_h_intr)
intersection_func(i_time, m_time, i_m_intr)
intersection_func(q_time, h_time, q_h_intr)
intersection_func(q_time, m_time, q_m_intr)
intersection_func(h_time, m_time, h_m_intr)

int min_idx(const std::vector<int> & a) {
    size_t m = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != INF) {
            m = i; break;
        }
    }
    /* m is first non-inf here, except if all inf */
    for (size_t i = m + 1; i < a.size(); ++i) {
        if (a[i] < a[m] && a[i] != INF) {
            m = i;
        }
    }

    return m;
}

/**
 * Returns a configuration structure for the sort routine.
 * Expects a bunch of data given as the data parameter. The testing data structures will
 * be the same as container_t. They must support random indexing and stl datastructure
 * interfaces. The algorithm uses user-supplied containers because container
 * implementation dictates the weights of member access versus member comparison etc. For
 * instance, if your data structure simulates a serial medium (list), mergesort will
 * perform much faster than the rest, since it is more in-order.
 * @param M upper bound for test container sizes. THis is the maximal number of elements
 * that sorting will be attempted for. Data is not required to be this long, but it helps.
 * If data is not long enough, duplicate elements will be drawn from it.
 * @param iterations the number of iterations that will be done sorting. The larger, the
 * more exact the measurement. This is a suggestion for the algorithm.
 * @param limit the number of elements algo is allowed to use. The
 * larger, the faster. MUST be at least as large as M
 * @param data the sample data. The order of the data elements is not important, they will
 * be randomly chosen for each test. This data should match your typical dataset closely,
 * since that will make the bounds better.
 */
template <typename container_t>
conf_t learn(const size_t M, size_t iterations, size_t limit, container_t& data) {
    std::cout << "M: " << M << ", iter: " << iterations << ", limit: " << limit << std::endl;

    std::vector<char> legend(4);
    legend[INSERTION] = 'i';
    legend[QUICK]     = 'q';
    legend[HEAP]      = 'h';
    legend[MERGE]     = 'm';

    std::vector<std::vector<int> > graph;
    graph.resize(4);
    for (size_t i = 0; i < graph.size(); ++i) {
        graph[i].resize(4);
        for (size_t j = 0; j < graph[i].size(); ++j) {
            graph[i][j] = INF; /* default */
        }
    }

    ///////////  MAKING GRAPH  //////////////
    int point;
    point = i_q_intr(M, iterations, limit, data);
    std::cout << "point (i, q): " << point << std::endl;
    if (point > 0 || point == INF) graph[INSERTION][QUICK] = point;
    else graph[QUICK][INSERTION] = -point;

    point = i_h_intr(M, iterations, limit, data);
    std::cout << "point (i, h): " << point << std::endl;
    if (point > 0 || point == INF) graph[INSERTION][HEAP] = point;
    else graph[HEAP][INSERTION] = -point;

    point = i_m_intr(M, iterations, limit, data);
    std::cout << "point (i, m): " << point << std::endl;
    if (point > 0 || point == INF) graph[INSERTION][MERGE] = point;
    else graph[MERGE][INSERTION] = -point;

    point = q_h_intr(M, iterations, limit, data);
    std::cout << "point (q, h): " << point << std::endl;
    if (point > 0 || point == INF) graph[QUICK][HEAP] = point;
    else graph[HEAP][QUICK] = -point;

    point = q_m_intr(M, iterations, limit, data);
    std::cout << "point (q, m): " << point << std::endl;
    if (point > 0 || point == INF) graph[QUICK][MERGE] = point;
    else graph[MERGE][QUICK] = -point;

    point = h_m_intr(M, iterations, limit, data);
    std::cout << "point (h, m): " << point << std::endl;
    if (point > 0 || point == INF) graph[HEAP][MERGE] = point;
    else graph[MERGE][HEAP] = -point;

    /** cout graph **/
    for (size_t i = 0; i < legend.size(); ++i) { std::printf("   %c  ", legend[i]); }
    std::printf("\n");
    for (size_t i = 0; i < graph.size(); ++i) {
        std::printf("%c ", legend[i]);
        for (size_t j = 0; j < graph[i].size(); j++) {
            std::printf("% 5d", graph[i][j]);
        }
        std::printf("\n");
    }

    ////////////  MAKING CONF  //////////////
    /* find start */
    size_t root = 0;
    for (size_t i = 0; i < graph.size(); ++i) {
        bool k = true;
        for (size_t j = 0; j < graph[i].size(); ++j) {
            if (graph[j][i] != INF) {
                k = false; break;
            }
        }
        if (k) {
            root = i;
            break;
        }
    }

    /* follow minimum */
    conf_t path;
    size_t c = 1, idx;
    while (c < graph.size()) {
        idx = min_idx(graph[root]);
        if (graph[root][idx] != INF) {
            path.push_back(std::make_pair(legend[root], graph[root][idx]));
            root = idx;
        }
        ++c;
    }
    path.push_back(std::make_pair(legend[root], -1));

    return path;
}

} // tweaksort
#endif
