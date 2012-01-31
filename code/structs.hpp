#ifndef STRUCTS_HPP

#include <iostream>
#include <time.h>
#include <cmath>
#include <vector>

template<class T>
/**
 * Prints a stl container.
 * @param arr Container to be printed. Must support size method and operator[].
 */
void print (T arr) {
    std::cout << "[";
    size_t i = 0;
    for (; i + 1 < arr.size(); ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[i];
    std::cout << "]" << std::endl;
}

double take_time(int x) {
    return sin(cos(tan(sin(cos(tan(cos(sin(tan(cos(sin(x*x*x*x - x*x*x)))))))))));
}

/**
 * Struct whose comparison takes unbearbly long time.
 */
struct Slow {
    int x;
    Slow(int _x) : x(_x) {}
    Slow() : x(0) {}
    bool operator<(const Slow &o) const {
        double y = take_time(o.x);
        return x + y < o.x + y;
    }
};

/**
 * Struct whose copying takes unbearably long time. 
 */
struct Huge {
    int x;
    std::vector<double> a;
    Huge(int _x) : x(_x), a(100, 12.5) {}
    Huge() : x(0), a(100, 12.5) {}
    bool operator<(const Huge &o) const {
        return x < o.x;
    }
};
#define STRUCTS_HPP
#endif
