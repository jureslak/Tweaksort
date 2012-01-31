#include "all-i-need.h"

//double q_time(int size, int num, int limit) {
//    int cur_pos = 0;
//    double delta = 0;
//    timeval start, end;
//    vector<vector<int> > a;
//    while (cur_pos < num) {
//        get_shuffled_vectors(size, limit, cur_pos, num, a);
//        int sz = a.size();
//        gettimeofday(&start, NULL);
//        for (int i = 0; i < sz; ++i) {
//            quick_sort(a[i].begin(), a[i].end());
//        }
//        gettimeofday(&end, NULL);
//        delta += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
//    }
//    return delta / num;
//}

//double i_time(int size, int num, int limit) {
//    int cur_pos = 0;
//    double delta = 0;
//    timeval start, end;
//    vector<vector<int> > a;
//    while (cur_pos < num) {
//        get_shuffled_vectors(size, limit, cur_pos, num, a);
//        int sz = a.size();
//        gettimeofday(&start, NULL);
//        for (int i = 0; i < sz; ++i) {
//            insertion_sort(a[i].begin(), a[i].end());
//        }
//        gettimeofday(&end, NULL);
//        delta += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
//    }
//    return delta / num;
//}

#define timefunc(sort, name) \
double name(int size, int num, int limit)\
{\
    int cur_pos = 0;\
    double delta = 0;\
    timeval start, end;\
    vector<vector<int> > a;\
    while (cur_pos < num) {\
        get_shuffled_vectors(size, limit, cur_pos, num, a);\
        int sz = a.size();\
        gettimeofday(&start, NULL);\
        for (int i = 0; i < sz; ++i) {\
            sort(a[i].begin(), a[i].end());\
        }\
        gettimeofday(&end, NULL);\
        delta += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;\
    }\
    return delta / num;\
}

timefunc(insertion_sort, i_time);
timefunc(quick_sort, q_time);
timefunc(merge_sort, m_time);
timefunc(heap_sort, h_time);

#define INF (-1)

#define intersection_func(sort1, sort2, name) \
int name(int M, int precision, const char * limit) { \
    int m = 5;\
    double max_time_sort1 = sort1(M, precision, get_limit(limit));\
    double max_time_sort2 = sort2(M, precision, get_limit(limit));\
\
    double max_d = max_time_sort1 - max_time_sort2;\
    double min_d = -max_d; /* nasprotni predznak, da se začne bisekcija */ \
\
    double t_sort1, t_sort2, t_d;\
    while (M - m > 1) {\
        t_sort1 = sort1((m+M)/2, precision, get_limit(limit));\
        t_sort2 = sort2((m+M)/2, precision, get_limit(limit));\
        t_d = t_sort1 - t_sort2; \
        if (t_d < 0 && max_d < 0 || t_d > 0 && max_d > 0) { \
            M = (M+m)/2;\
        } else {\
            m = (M+m)/2;\
        }\
    }\
    return (m == 5) ? INF : ((max_time_sort1 > max_time_sort2) ? m : -m); \
}\

intersection_func(i_time, q_time, i_q_intr);
intersection_func(i_time, h_time, i_h_intr);
intersection_func(i_time, m_time, i_m_intr);
intersection_func(q_time, h_time, q_h_intr);
intersection_func(q_time, m_time, q_m_intr);
intersection_func(h_time, m_time, h_m_intr);

#define INSERTION 0
#define QUICK 1
#define HEAP 2
#define MERGE 3

template <typename T>
int min_idx(T a) {
    if (a.size() < 0) cout << "a below 1"<< endl;
    int m = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != INF) {
            m = i; break;
        }
    }

    for (int i = m + 1; i < a.size(); ++i) {
        if (a[i] < a[m] && a[i] != INF) {
            m = i;
        }
    }
    return m;
}


int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "Help: " << endl;
        cout << "Param 1: M ......... Most elements to be sorted" << endl;
        cout << "Param 2: PREC ...... How many times to run sort for single length" << endl;
        cout << "Param 3: MEM_LIM ... Limit of memory (how much can I use?)" << endl;
    }
    assert(argc == 4);

    int M, PREC;
    char MEM_LIM [7];
    sscanf(argv[1], "%d", &M);
    sscanf(argv[2], "%d", &PREC);
    sscanf(argv[3], "%s", MEM_LIM);

    vector<char> legend;
    legend.push_back('i');
    legend.push_back('q');
    legend.push_back('h');
    legend.push_back('m');

    vector<vector<int> > graph;
    graph.resize(4);
    for (int i = 0; i < graph.size(); ++i) {
        graph[i].resize(4);
        for (int j = 0; j < graph[i].size(); ++j) {
            graph[i][j] = INF;
        }
    } /* default */

    int point;
    point = i_q_intr(M, PREC, MEM_LIM);
    cout << "point (i, q): " << point << endl;
    if (point > 0 || point == INF) graph[INSERTION][QUICK] = point;
    else graph[QUICK][INSERTION] = -point;

    point = i_h_intr(M, PREC, MEM_LIM);
    cout << "point (i, h): " << point << endl;
    if (point > 0 || point == INF) graph[INSERTION][HEAP] = point;
    else graph[HEAP][INSERTION] = -point;

    point = i_m_intr(M, PREC, MEM_LIM);
    cout << "point (i, m): " << point << endl;
    if (point > 0 || point == INF) graph[INSERTION][MERGE] = point;
    else graph[MERGE][INSERTION] = -point;

    point = q_h_intr(M, PREC, MEM_LIM);
    cout << "point (q, m): " << point << endl;
    if (point > 0 || point == INF) graph[QUICK][HEAP] = point;
    else graph[HEAP][QUICK] = -point;

    point = q_m_intr(M, PREC, MEM_LIM);
    cout << "point (q, m): " << point << endl;
    if (point > 0 || point == INF) graph[QUICK][MERGE] = point;
    else graph[MERGE][QUICK] = -point;

    point = h_m_intr(M, PREC, MEM_LIM);
    cout << "point (h, m): " << point << endl;
    if (point > 0 || point == INF) graph[HEAP][MERGE] = point;
    else graph[MERGE][HEAP] = -point;

    printf("----------------------\n");

    /** cout graph **/
    for (int i = 0; i < legend.size(); ++i) { printf("   %c  ", legend[i]); }
    printf("\n");
    for (int i = 0; i < graph.size(); ++i) {
        printf("%c ", legend[i]);
        for (int j = 0; j < graph[i].size(); j++) {
            printf("% 5d", graph[i][j]);
        }
        printf("\n");
    }


    int root;
    for (int i = 0; i < graph.size(); ++i) {
        bool k = true;
        for (int j = 0; j < graph[i].size(); ++j) {
            if (graph[j][i] != INF) {
                k = false; break;
            }
        }
        if (k) {
            root = i;
            break;
        }
    }

    vector<pair<char, int> > path;

    int c = 1, idx, line = root;
    while (c < graph.size()) {
        idx = min_idx(graph[root]);
        if (graph[line][idx] != INF) {
            path.push_back(make_pair(legend[root], graph[line][idx]));
            line = root;
            root = idx;
        }
        ++c;
    }
    path.push_back(make_pair(legend[root], -1));


    FILE *file_conf;  /* output-file pointer */
    const char *file_conf_file_name = "sort.conf";  /* output-file name    */

    file_conf = fopen(file_conf_file_name, "w");
    if (file_conf == NULL) {
        fprintf(stderr, "couldn't open file '%s'; %s\n", file_conf_file_name, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("----------------------\n");
    for (int i = 0; i < path.size(); ++i) {
        fprintf(file_conf, "%c -> %d\n", path[i].first, path[i].second);
        fprintf(stdout, "%c -> %d\n", path[i].first, path[i].second);
    }

    if (fclose(file_conf) == EOF) {           /* close output file   */
        fprintf(stderr, "couldn't close file '%s'; %s\n", file_conf_file_name, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return 0;
}
