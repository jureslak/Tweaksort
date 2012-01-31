#ifndef MERGE_HPP
#define MERGE_HPP
/**
 * @file m.hpp
 * File where merge sort algorithm is implemented.
 *
 * @author Jure Slak <jure.slak@gmail.com>
 * @version 1.0
 */
#include <vector>

namespace tweaksort
{

/** 
 * Sorts data structure using mergesort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last)
{
    if (last - first < 2) return;
    RandomAccessIterator middle = first + (last - first) / 2;
    merge_sort(first, middle);
    merge_sort(middle, last);
    merge(first, middle, last);
}

/**
 * Merges two sorted data structures in one sorted data structure.
 * @param first Iterator pointing at the first element of first data structure.
 * @param middle Iterator pointing past the last element of first data structure and
 * pointing to the fisrt element of second data structure.
 * @param last Iterator pointing past the last element of second data structure.
 * @return None.
 */
template<typename RandomAccessIterator>
void merge(RandomAccessIterator first, RandomAccessIterator middle,
        RandomAccessIterator last)
{
    if (last - first < 2) return;

    std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> tmp;
    RandomAccessIterator i = first, j = middle;

    /* merging sorted lists */
    while ((i < middle) && (j < last)) {
        if (*i < *j) {
           tmp.push_back(*i);
           ++i;
        } else {
           tmp.push_back(*j);
           ++j;
        }
    }

    /* adding the rest of array */
    while (i < middle) {
        tmp.push_back(*i);
        ++i;
    }
    while (j < last) {
        tmp.push_back(*j);
        ++j;
    }

    /* copying back */
    i = tmp.begin();
    while (i < tmp.end()){
        *first = *i;
        ++first;
        ++i;
    }
}

}

#endif
