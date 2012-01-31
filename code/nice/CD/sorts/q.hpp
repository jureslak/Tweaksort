#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP
/**
 * @file q.hpp
 * File where quicksort algorithm is implemented.
 *
 * @author Jure Slak <jure.slak@gmail.com>
 * @version 1.0
 */

#include <algorithm> //swap

namespace tweaksort
{

/** 
 * Sorts data structure using quicksort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (last - first < 2) return; // konec
    RandomAccessIterator s = first;
    RandomAccessIterator e = last - 1;
    RandomAccessIterator m = s + (e - s) / 2;

    /* choosing pivot as median of strat end and middle */
    if ((*m < *s && *s < *e) || (*e < *s && *s < *m)) {
        std::swap(*s, *e);
    } else if ((*e < *m && *m < *s) || (*s < *m && *m < *e)) {
        std::swap(*m, *e);
    }

    typename std::iterator_traits<RandomAccessIterator>::value_type pivot = *e;

    --e;

    while (s <= e) {
        while (s <= e && !(pivot < *s)) { ++s; }
        while (s <= e && pivot < *e) { --e; }
        if (s < e) {
            std::swap(*s, *e);
        }
    }
    last[-1] = *s;
    *s = pivot;
    quick_sort(first, s);
    quick_sort(s + 1, last);
}

} // tweaksort
#endif
