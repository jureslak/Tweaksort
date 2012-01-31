#ifndef INSERTION_HPP
#define INSERTION_HPP

/**
 * @file i.hpp
 * File where insertion sort algorithm is implemented.
 *
 * @author Jure Slak <jure.slak@gmail.com>
 * @version 1.0
 */

namespace tweaksort
{

/** 
 * Sorts data structure using insertion sort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (last - first < 2) return;
    RandomAccessIterator i = first + 1;
    typename std::iterator_traits<RandomAccessIterator>::value_type tmp;
    while (i < last) {
        tmp = *i;
        RandomAccessIterator j = i - 1;
        while (j >= first && tmp < *j) {
            j[1] = *j;
            --j;
        }
        j[1] = tmp;
        ++i;
    }
}

} // tweaksort

#endif
