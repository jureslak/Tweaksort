#include "structs.hpp"
#include "sort.hpp"
#include "m.hpp"
#include "q.hpp"
#include "i.hpp"
#include "s.hpp"
#include "h.hpp"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <list>
#include <cassert>
#include <fstream>
#include <sys/time.h>
#include <cstdlib>

using std::cout;
using std::endl;
using namespace tweaksort;

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
    assert(data.size() > 0); \
    double delta = 0;\
    timespec start, end;\
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
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); \
        for (size_t i = 0; i < length; ++i) {\
            sort(test[i].begin(), test[i].end());\
        }\
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); \
        delta += (end.tv_sec - start.tv_sec)*1e9 + (end.tv_nsec - start.tv_nsec);\
    }\
    return delta / iterations;\
}

timefunc(insertion_sort, i_time)
timefunc(selection_sort, s_time)
timefunc(quick_sort, q_time)
timefunc(merge_sort, m_time)
timefunc(heap_sort, h_time)
timefunc(std::sort, c_time)

template <class container_t>
double t_time(size_t N, size_t iterations, size_t limit, container_t &data, conf_t &conf)
{
    assert(limit >= N);
    assert(data.size() > 0);
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
//        std::cout << "in while, filling" << std::endl;
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

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        cout << "Help" << endl;
        cout << "param 1: M ............................ upper bound for sorting" << endl;
        cout << "param 1: a ............................ base for exp sorting" << endl;
        cout << "param 2: [iter = 1] ................... how many iterations to make" << endl;
        cout << "param 3: [limit = (M - 1) * iter] ..... how many iterations to make" << endl;
        cout << "param 4: [type = 1111] ................. int, string, huge or slow 1 if yes 0 otherwise" << endl;
        return 0;
    }
    assert(argc = 5);
    std::srand(std::time(NULL));
    int M, iter, limit;
    float a;
    std::string type;
    sscanf(argv[1], "%d", &M);
    sscanf(argv[2], "%f", &a);
    sscanf(argv[3], "%d", &iter);
    sscanf(argv[4], "%d", &limit);
    type = argv[5];

    std::clog << "M:     " << M << endl;
    std::clog << "a:     " << a << endl;
    std::clog << "iter:  " << iter << endl;
    std::clog << "limit: " << limit << endl;
    std::clog << "type: " << type << endl;

    assert(type.size() == 4);
    assert(a > 1);

    char t_int, t_string, t_huge, t_slow;
    sscanf(type.c_str(), "%c%c%c%c", &t_int, &t_string, &t_huge, &t_slow);

    assert(t_int == '0'    || t_int == '1');
    assert(t_string == '0' || t_string == '1');
    assert(t_huge == '0'   || t_huge == '1');
    assert(t_slow == '0'   || t_slow == '1');

    fixed(cout);
    boolalpha(cout);

    std::ifstream c1, c2, c3, c4;
    c1.open("int.conf");
    c2.open("string.conf");
    c3.open("huge.conf");
    c4.open("slow.conf");

    std::string s1, s2, s3, s4;
    std::getline(c1, s1);
    std::getline(c2, s2);
    std::getline(c3, s3);
    std::getline(c4, s4);

    tweaksort::conf_t conf1 (s1);
    tweaksort::conf_t conf2 (s2);
    tweaksort::conf_t conf3 (s3);
    tweaksort::conf_t conf4 (s4);

    std::vector<int> test_data1;
    std::vector<std::string> test_data2;
    std::vector<Huge> test_data3;
    std::vector<Slow> test_data4;

    if (t_int == '1') {
        for (int j = 1; j < M; ++j) {
            test_data1.push_back(j);
        }
    }

    if (t_string == '1') {
        std::ifstream txt ("rtext.txt");
        std::string s;
        for (int j = 1; j < M; ++j) {
            txt >> s;
            test_data2.push_back(s);
        }
        txt.close();
    }

    if (t_huge == '1') {
        for (int j = 1; j < M; ++j) {
            test_data3.push_back(Huge(j));
        }
    }

    if (t_slow == '1') {
        for (int j = 1; j < M; ++j) {
            test_data4.push_back(Slow(j));
        }
    }

    int i = a;
    for(int j = 1; i < M; ++j, i = pow(a, j)) {
        cout << "ln: " << i << endl;
        std::clog << "ln: " << i << endl;


        if (t_int == '1') cout << "ii: " << i_time(i, iter, limit, test_data1) << endl;
        else cout << "ii: -1" << endl;
        if (t_string == '1') cout << "is: " << i_time(i, iter, limit, test_data2) << endl;
        else cout << "is: -1" << endl;
        if (t_huge == '1') cout << "ih: " << i_time(i, iter, limit, test_data3) << endl;
        else cout << "ih: -1" << endl;
        if (t_slow == '1') cout << "is: " << i_time(i, iter, limit, test_data4) << endl;
        else cout << "is: -1" << endl;

        if (t_int == '1') cout << "si: " << s_time(i, iter, limit, test_data1) << endl;
        else cout << "si: -1" << endl;
        if (t_string == '1') cout << "ss: " << s_time(i, iter, limit, test_data2) << endl;
        else cout << "ss: -1" << endl;
        if (t_huge == '1') cout << "sh: " << s_time(i, iter, limit, test_data3) << endl;
        else cout << "sh: -1" << endl;
        if (t_slow == '1') cout << "ss: " << s_time(i, iter, limit, test_data4) << endl;
        else cout << "ss: -1" << endl;

        if (t_int == '1') cout << "qi: " << q_time(i, iter, limit, test_data1) << endl;
        else cout << "qi: -1" << endl;
        if (t_string == '1') cout << "qs: " << q_time(i, iter, limit, test_data2) << endl;
        else cout << "qs: -1" << endl;
        if (t_huge == '1') cout << "qh: " << q_time(i, iter, limit, test_data3) << endl;
        else cout << "qh: -1" << endl;
        if (t_slow == '1') cout << "qs: " << q_time(i, iter, limit, test_data4) << endl;
        else cout << "qs: -1" << endl;

        if (t_int == '1') cout << "hi: " << h_time(i, iter, limit, test_data1) << endl;
        else cout << "hi: -1" << endl;
        if (t_string == '1') cout << "hs: " << h_time(i, iter, limit, test_data2) << endl;
        else cout << "hs: -1" << endl;
        if (t_huge == '1') cout << "hh: " << h_time(i, iter, limit, test_data3) << endl;
        else cout << "hh: -1" << endl;
        if (t_slow == '1') cout << "hs: " << h_time(i, iter, limit, test_data4) << endl;
        else cout << "hs: -1" << endl;

        if (t_int == '1') cout << "mi: " << m_time(i, iter, limit, test_data1) << endl;
        else cout << "mi: -1" << endl;
        if (t_string == '1') cout << "ms: " << m_time(i, iter, limit, test_data2) << endl;
        else cout << "ms: -1" << endl;
        if (t_huge == '1') cout << "mh: " << m_time(i, iter, limit, test_data3) << endl;
        else cout << "mh: -1" << endl;
        if (t_slow == '1') cout << "ms: " << m_time(i, iter, limit, test_data4) << endl;
        else cout << "ms: -1" << endl;

        if (t_int == '1') cout << "ci: " << c_time(i, iter, limit, test_data1) << endl;
        else cout << "ci: -1" << endl;
        if (t_string == '1') cout << "cs: " << c_time(i, iter, limit, test_data2) << endl;
        else cout << "cs: -1" << endl;
        if (t_huge == '1') cout << "ch: " << c_time(i, iter, limit, test_data3) << endl;
        else cout << "ch: -1" << endl;
        if (t_slow == '1') cout << "cs: " << c_time(i, iter, limit, test_data4) << endl;
        else cout << "cs: -1" << endl;

        /* tweaksort sort */

        if (t_int == '1') cout << "ti: " << t_time(i, iter, limit, test_data1, conf1) << endl;
        else cout << "ti: -1" << endl;
        if (t_string == '1') cout << "ts: " << t_time(i, iter, limit, test_data2, conf2) << endl;
        else cout << "ts: -1" << endl;
        if (t_huge == '1') cout << "th: " << t_time(i, iter, limit, test_data3, conf3) << endl;
        else cout << "th: -1" << endl;
        if (t_slow == '1') cout << "ts: " << t_time(i, iter, limit, test_data4, conf4) << endl;
        else cout << "ts: -1" << endl;
    }

    cout << "Done!" << endl;
    std::clog << endl;
    return 0;
}
