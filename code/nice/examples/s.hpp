#ifndef SELECTION_HPP
#define SELECTION_PPP
/**
 * @file s.hpp
 * File where selection sort algorithm is implemented.
 *
 * @author Jure Slak <jure.slak@gmail.com>
 * @version 1.0
 */

#include <algorithm> //swap

namespace tweaksort
{

/** 
 * Sorts data structure using selection sort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator>
void selection_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (last - first < 2) return;
    RandomAccessIterator i, j;
    while (first < last - 1) {
        i = first;
        j = i + 1;
        while (j < last) {
            if (*j < *i) {
                i = j;
            }
            ++j;
        }
        std::swap(*i, *first);
        ++first;
    }
}

} //tweaksort
#endif
