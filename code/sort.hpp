#ifndef TWEAKSORT_SORT_HPP
#define TWEAKSORT_SORT_HPP
/**
 * @file sort.hpp
 * File where composite sort (tweaksort) algorithm is implemented.
 *
 * @author Jure Slak <jure.slak@gmail.com>
 * @version 1.0
 */
/*!
 * \mainpage 
 * The purpose of the research paper is to find an optimal sorting algorithm. In
 * the first part of the paper the theory of sorting, various sorting
 * algorithms and their expected behaviour on actual data are described. Two
 * hypotheses regarding efficiency of sorting algorithms are also set.
 * The next part describes the idea on which the composite sorting algorithm is based and
 * how it is configured. An important part is the
 * theoretical derivation of the algorithm which finds the optimal configuration
 * for the composite sorting algorithm by comparing efficiency of each sorting
 * algorithm. The description of the implementation of this algorithm is also given and
 * followed by presentation of results. Results illustrate the comparison of
 * efficiency for each sorting algorithm on different types of data. The obtained
 * results are then explained in terms of theoretical basics and both hypotheses are evaluated on the basis
 * of our findings. The result of the research paper is an efficient and extremely
 * adaptive composite sorting algorithm, which can adapt to the capabilities
 * of hardware as well to the data being sorted.
 * 
 */
#include "conf.hpp"

#define INF size_t(-1)
#include <vector>

namespace tweaksort
{
template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last, const conf_t & conf);

/** 
 * Sorts data structore using heapsort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator> // heap sort
void tw_heap_sort(RandomAccessIterator first, RandomAccessIterator last) {
    // can't recurse into other sorts
    tw_heapify(first, last);

    --last;
    while (last > first) {
        std::swap(*last, *first);
        --last;
        tw_siftDown(first, first, last);
    }
}

template<typename RandomAccessIterator> // heapify
/** 
 * Function used by heapsort routine.
 * Heapifys everything in range [first, last).
 * @param first Iterator pointing fo first element being heapified.
 * @param last Iterator pointing past the last element being heapified.
 * @return None.
 */
void tw_heapify(RandomAccessIterator first, RandomAccessIterator last) {
    RandomAccessIterator start = first + (last - first)/2 - 1;
    while (start >= first) {
        tw_siftDown(first, start, last-1);
        --start;
    }
}

/**
 * Sifts an element at the root place down the heap.
 * Heap is presented in intervval [root, last].
 * @param first Iterator pointing at first element of data structure, used only to calculate
 * @param first Iterator pointing at first element of heap. This is the value that is
 * sifted.
 * @param last Points at the last element of the heap. Or past the last??
 * @return None.
 */
template<typename RandomAccessIterator> // siftDown
void tw_siftDown( RandomAccessIterator begin, RandomAccessIterator root, RandomAccessIterator last) {
    size_t offset = root - begin;

    while (root + offset < last) { // until we have reached the end of array
        // current parent is
        // root =   start + offset,
        // child1 = start + 2*offset + 1
        // child2 = start + 2*offset + 2
        RandomAccessIterator child = root + offset + 1;
        RandomAccessIterator swap   = root;
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
        } else { return; }
        offset = root - begin;
    }
}

/** 
 * Sorts data structore using insertion sort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator> // insertion
void tw_insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
    // also the last one, can't recurse
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


/** 
 * Sorts data structore using quicksort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @param conf Configuration for main sort routine.
 * @return None.
 */
template<typename RandomAccessIterator> // quick
void tw_quick_sort(RandomAccessIterator first, RandomAccessIterator last, const conf_t & conf) {
    // can recurse
    RandomAccessIterator s = first;
    RandomAccessIterator e = last - 1;
    RandomAccessIterator m = s + (e - s) / 2;

    /* choosing pivot as median of strat end and middle */
    if ((*s < *e && !(*s < *m)) || (!(*s < *e) && *s < *m)) {
        std::swap(*s, *e);
    } else if ((*m < *s && !(*m < *e)) || (!(*m < *s) && *m < *e)) {
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

    ::tweaksort::sort(first, s, conf);
    ::tweaksort::sort(s + 1, last, conf);
}

/** 
 * Sorts data structore using mergesort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @param conf Configuration for main sort routine.
 * @return None.
 */
template<typename RandomAccessIterator> // merge_sort
void tw_merge_sort(RandomAccessIterator first, RandomAccessIterator last, const conf_t & conf) {
    // can recurse
    RandomAccessIterator middle = first + (last - first) / 2;
    ::tweaksort::sort(first, middle, conf);
    ::tweaksort::sort(middle, last, conf);
    tw_merge(first, middle, last);
}
/**
 * Merges two sorted data structures in one sorted data structure.
 * @param first Iterator pointing at the first element of first data structure.
 * @param middle Iterator pointing past the last element of first data structure and
 * pointing to the fisrt element of second data structure.
 * @param last Iterator pointing past the last element of second data structure.
 * @return None.
 */
template<typename RandomAccessIterator> // merge
void tw_merge(RandomAccessIterator first, RandomAccessIterator middle,
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

    /* copying ne one back */
    i = tmp.begin();
    while (i < tmp.end()){
        *first = *i;
        ++first;
        ++i;
    }
}

/** 
 * Sorts data structore using selection sort algorithm. 
 * Sorts everything in range [first, last).
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @return None.
 */
template<typename RandomAccessIterator> // selection
void tw_selection_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (last - first < 2) return;
    RandomAccessIterator i, j;
    while (first < last) {
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
/**
 * Alternative version of get_sort.
 * User for fool to search the conf.
 * @param n Length of data structure.
 * @param conf Configuration.
 * @return Optimal sorting algortihm ID.
 */
inline sort_e get_sort_1(size_t n, const conf_t& conf)
{
    size_t len = conf.size();
    for (size_t i = 0; i < len; ++i) {
        if (n <= conf[i].second) {
            return conf[i].first;
        }
    }
    throw ParseError("Don't know which sort to use!");
    return HEAPSORT;
}

/**
 * Finds the right sorting algo by bisection.
 * @param n Length of data structure.
 * @param conf Configuration.
 * @return Optimal sorting algortihm ID for this length.
 */
inline sort_e get_sort(size_t n, const conf_t& conf)
{
    size_t start = 0, length = conf.size(), len = conf.size() >> 1;
    while (len > 0) {

        size_t middle = start + len;
        size_t left  = conf[middle-1].second;
        if (middle == length) {
            return conf[middle-1].first;
        }
        size_t right = conf[middle].second;

        if (n > right) {
            start = middle + 1;
        } else if (n > left) { // in between
            return conf[middle].first;
        }
        len >>= 1;
    }
    return conf[start].first;
}

/** 
 * Sorts data structore using tweaksort algorithm. 
 * Sorts everything in range [first, last).
 * Searceh the conf using bisection log(n) complexitiy.
 * @param first Iterator pointing to first object being sorted.
 * @param last Iterator pointing past the last element being sorted.
 * @param conf Configuration for the sort.
 * @return None.
 */
template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last, const conf_t & conf) {
    size_t len = last - first;
    if (len < 2) return;


    sort_e s = get_sort(len, conf);

//    std::cout << "choice vvv" << std::endl;
//    std::cout << conf.str() << std::endl;
//    std::cout << len << std::endl;
//    std::cout << enum_to_char(s) << std::endl;

    switch (s) {
        case INSERTIONSORT: tw_insertion_sort(first, last); break;
        case SELECTIONSORT: tw_selection_sort(first, last); break;
        case QUICKSORT:     tw_quick_sort(first, last, conf); break;
        case HEAPSORT:      tw_heap_sort(first, last); break;
        case MERGESORT:     tw_merge_sort(first, last, conf); break;
    };
}

} // tweaksort
// vim: ts=4 sw=4 expandtab
#endif
