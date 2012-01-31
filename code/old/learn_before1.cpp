#include "structs.hpp"
#include "conf.hpp"
#include "learn.hpp"

#include <iostream>
#include <algorithm>
#include <list>
#include <cassert>
#include <fstream>

using std::cout;
using std::endl;
using tweaksort::conf_t;
using tweaksort::Compare;
using tweaksort::make_compare;

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        cout << "Help" << endl;
        cout << "param 1: M ........ upper bound for learning" << endl;;
        cout << "param 2: ITER ..... how many iterations to make" << endl;
        cout << "param 3: INC ...... how much to increment the distance every time" << endl;
        cout << "param 4: LIMIT .... how many elements are allowed in memory" << endl;
        cout << "param 5: TYPE ..... int, string, huge or slow 1 if yes 0 otherwise" << endl;
        return 0;
    }
    assert(argc == 6);
    int M, ITER, LIMIT;
    float INC;
    sscanf(argv[1], "%d", &M);
    sscanf(argv[2], "%d", &ITER);
    sscanf(argv[3], "%f", &INC);
    sscanf(argv[4], "%d", &LIMIT);

    char t_int, t_string, t_huge, t_slow;
    sscanf(argv[5], "%c%c%c%c", &t_int, &t_string, &t_huge, &t_slow);

    assert(t_int == '0'    || t_int == '1');
    assert(t_string == '0' || t_string == '1');
    assert(t_huge == '0'   || t_huge == '1');
    assert(t_slow == '0'   || t_slow == '1');

    cout << ":::::::::::::::::::::::::::::start" << endl;
    cout << "readwrite test: " << ((tweaksort::read_write_test()) ? "PASSED" : "FAILED") << endl;
    srand(time(NULL));

    std::vector<int> test_data1;
    std::vector<std::string> test_data2;
    std::vector<Huge> test_data3;
    std::vector<Slow> test_data4;

    if (t_int == '1') {
        for (int j = 0; j < M; ++j) {
            test_data1.push_back(j);
        }
    }

    if (t_string == '1') {
        std::ifstream txt ("rtext.txt");
        std::string s;
        for (int j = 0; j < M; ++j) {
            txt >> s;
            test_data2.push_back(s);
        }
        txt.close();
    }

    if (t_huge == '1') {
        for (int j = 0; j < M; ++j) {
            test_data3.push_back(Huge(j));
        }
    }

    if (t_slow == '1') {
        for (int j = 0; j < M; ++j) {
            test_data4.push_back(Slow(j));
        }
    }

    std::random_shuffle(test_data1.begin(), test_data1.end());
    std::random_shuffle(test_data2.begin(), test_data2.end());
    std::random_shuffle(test_data3.begin(), test_data3.end());
    std::random_shuffle(test_data4.begin(), test_data4.end());

    if (t_int == '1') {
        cout << ":::::::::: INT ::::::::::::::before learn" << endl;
        Compare<std::vector<int>> cmp1 (ITER, LIMIT, INC, test_data1);
        tweaksort::conf_t conf = tweaksort::learn(M, make_compare(ITER, LIMIT, INC,
                    test_data1));
        cout << "conf1: " << conf.str() << endl;
        std::ofstream txt("int.conf");
        txt << conf.str() << endl;
        txt.close();
    }
    if (t_huge == '1') {
        cout << ":::::::::: HUGE :::::::::::::before learn" << endl;
        Compare<std::vector<Huge>> cmp1 (ITER, LIMIT, INC, test_data3);
        tweaksort::conf_t conf = tweaksort::learn(M, cmp1);
        cout << "conf1: " << conf.str() << endl;
        std::ofstream txt("huge.conf");
        txt << conf.str() << endl;
        txt.close();
    }
    if (t_slow == '1') {
        cout << ":::::::::: SLOW :::::::::::::before learn" << endl;
        // %% zakaj je tuki treba narest compare objekt
        Compare<std::vector<Slow>> cmp1 (ITER, LIMIT, INC, test_data4);
        tweaksort::conf_t conf = tweaksort::learn(M, cmp1);
        cout << "conf1: " << conf.str() << endl;
        std::ofstream txt("slow.conf");
        txt << conf.str() << endl;
        txt.close();
    }
    if (t_string == '1') {
        cout << ":::::::::: STRING :::::::::::before learn" << endl;
        Compare<std::vector<std::string>> cmp1 (ITER, LIMIT, INC, test_data2);
        tweaksort::conf_t conf = tweaksort::learn(M, cmp1);
        cout << "conf1: " << conf.str() << endl;
        std::ofstream txt("string.conf");
        txt << conf.str() << endl;
        txt.close();
    }
}
