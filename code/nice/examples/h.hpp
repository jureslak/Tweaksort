#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP
/**
 * @file h.hpp
 * File where heapsort algorithm is implemented.
 *
 * @author Jure Slak <jure.slak@gmail.com>
 * @version 1.0
 */

#include <algorithm> //swap

namespace tweaksort
{

/** 
 * Sorts data structure using heapsort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (last - first < 2) return; // if only one or zero elements

    heapify(first, last);

    --last;
    while (last > first) {
        std::swap(*last, *first);
        --last;
        siftDown(first, first, last);
    }
}

/** 
 * Function used by heapsort routine.
 * Heapifys everything in range [first, last).
 * @param first Iterator pointing fo first element being heapified.
 * @param last Iterator pointing past the last element being heapified.
 * @return None.
 */
template<typename RandomAccessIterator>
void heapify(RandomAccessIterator first, RandomAccessIterator last) {
    RandomAccessIterator start = first + (last - first)/2 - 1;
    while (start >= first) {
        siftDown(first, start, last-1);
        --start;
    }
}

/**
 * Sifts an element at the root place down the heap.
 * Heap is presented in interval [root, last].
 * @param first Iterator pointing at first element of data structure, used only to calculate
 * @param first Iterator pointing at first element of heap. This is the value that is
 * sifted.
 * @param last Points at the last element of the heap. Or past the last??
 * @return None.
 */
template<typename RandomAccessIterator>
void siftDown( RandomAccessIterator begin, RandomAccessIterator root,
        RandomAccessIterator last)
{
    size_t offset = root - begin;

    while (root + offset < last) { // until we have reached the end of array
        // current parent is
        // root =   start + offset,
        // child1 = start + 2*offset + 1
        // child2 = start + 2*offset + 2
        RandomAccessIterator child = root + offset + 1;
        RandomAccessIterator swap = root;
        if (*swap < *child) { // heap property is not satisfied
            swap = child; // by default, exchange with 1st child
        }
        // a) child2 must exist
        // b) swap is either still the root or child1. We must check whether the heap
        // property is satisfied with child2 as well, and swap the root with the larger
        // child, so that the heap property will be satisfied afterwards.
        if (child + 1 <= last && *swap < child[1]) {
            swap = child + 1;
        }
        if (swap != root) { // if the heap property was not satisfied
            std::swap(*swap, *root);
            root = swap;
            offset = root - begin;
        } else { return; }
    }
}

} // tweaksort

#endif
