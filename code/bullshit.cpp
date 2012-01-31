/**
 * @file bullshit.cpp
 * 
 *
 * @author Jure Slak (JS), jure.slak@gmail.com
 * @version 1.0
 * @since 2010-12-30 08:56:44 PM
 */

#include "all-i-need.h"

using namespace std;
struct A {
    int x, y;
    A(int _x, int _y) : x(_x), y(_y) {}
    friend ostream& operator<<(ostream& o, const A& a);
};

ostream& operator<<(ostream& o, const A& a){
    o << a.x << ", " << a.y;
    return o;
}

int testas[] = { 6, 0, 1, 5, 7, 3, 2, 4 };
vector<int> ab (testas, testas + sizeof(testas) / sizeof(int));

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
int main(int argc, char *argv[]) {
    A as(1, 0);
    cout << as << endl;
    conf_t a(":i --> 19;:q-->19;:i --> 33;:i --> 43;:i --> 46;:i --> 48;:q --> 53;:i --> 54;:i -->\
            55;:q --> 62;:q --> 67;:q --> 77;:q --> 79;:q --> 82;:m --> 94;:h -- > 106;:s --> \
            123;: h->678;");
//    conf_t a(":s --> 5;:i --> 7;:h --> 8;");
    conf_t b(":q->-1");
    cout << a << b << endl;
    conf_t c = a + b;
//    c.beautify();
    cout << c << endl;
    boolalpha(cout);

    vector<int> s = get_shuffled_vector(100);
    vector<int> s2 = s;


    std::sort(s2.begin(), s2.end());
    insertion_sort(s.begin(), s.end());
    cout << "insertionsort: " << (s == s2) << endl;
    std::random_shuffle(s.begin(), s.end());
    selection_sort(s.begin(), s.end());
    cout << "selectionsort: " << (s == s2) << endl;
    std::random_shuffle(s.begin(), s.end());
    quick_sort(s.begin(), s.end());
    cout << "quicksort: " << (s == s2) << endl;
    std::random_shuffle(s.begin(), s.end());
    heap_sort(s.begin(), s.end());
    cout << "heapsort: " << (s == s2) << endl;
    std::random_shuffle(s.begin(), s.end());
    merge_sort(s.begin(), s.end());
    cout << "mergesort: " << (s == s2) << endl;

    cout << c << endl;

    size_t len = 40;
    if (argc == 2) { sscanf(argv[1], "%d", (int*) &len); }

    timespec time1, time2;
    int temp;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i< 1; i++)
	    temp+=temp;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    cout<<diff(time1,time2).tv_sec<<":"<<diff(time1,time2).tv_nsec<<endl;

    print (ab);

    for (size_t i = 0; i < len; ++i) {
        if (i % 10 == 0) {
        cout << c << endl; }
        cout << i << ": ";
        cout << (get_sort(i, c) ==  get_sort_1(i, c));
        cout << ": " << enum_to_char(get_sort_1(i, c)) << endl;
    }

    return 0;
}
