#include "q.hpp"
#include "m.hpp"
#include "i.hpp"
#include "h.hpp"
#include "s.hpp"
#include "sort.hpp"
#include "learn.hpp"
#include "structs.hpp"

#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <utility>
#include <cerrno>
#include <fstream>

using std::vector;
using std::cout;
using std::endl;
using std::random_shuffle;
using std::iterator_traits;
using std::pair;
using std::make_pair;
using namespace tweaksort;

template<typename RAI>
void print(RAI a, RAI b) {
    cout << "[";
    while (a < b) {
       cout << *a << ((b - a > 1) ? ", " : "");
       ++a;
    }
    cout << "]" << endl;
}

vector<int> get_shuffled_vector(int s) {
    vector<int> a;
    for (int i = 0; i < s; ++i) {
        a.push_back(i);
    }
    random_shuffle(a.begin(), a.end());
    return a;
}

void get_shuffled_vectors(int vec_size, size_t mem_limit, int & cur_pos, int vec_limit, vector< vector < int> > & a) {
    while (sizeof (a) < mem_limit && cur_pos < vec_limit) {
        a.push_back(get_shuffled_vector(vec_size));
        ++cur_pos;
    }
}
