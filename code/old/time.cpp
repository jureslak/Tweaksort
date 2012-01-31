#include "all-i-need.h"

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        cout << "Help: " << endl;
        cout << "Param 1: type of sort" << endl;
        cout << "Param 2: from length" << endl;
        cout << "Param 3: to lenght" << endl;
        cout << "Param 4: number of repetitions for each length" << endl;
        cout << "Param 5: Memory limit" << endl;
        return 0;
    }
    assert(argc == 6);
    timeval on, off;
    gettimeofday(&on, NULL);
    srand(time(NULL)); // randomize random

    char name[11];
    sprintf(name, "%s_sort_data", argv[1]);
    FILE * data = fopen(name, "w");

    double delta = 0.0;
    int num, s, e, limit = get_limit(argv[5]);
    sscanf(argv[2], "%d", &s);
    sscanf(argv[3], "%d", &e);
    sscanf(argv[4], "%d", &num);

    timeval start, end;
//    gettimeofday()
    if (strcmp(argv[1], "q") == 0) {
        fprintf(data, "QUICK SORT\n");
        for (int j = s; j < e; ++j) {
            cout << e-j << " more to go" << endl;
            int cur_pos = 0;
            vector<vector<int> > a;
            while (cur_pos < num) {
                get_shuffled_vectors(j, limit, cur_pos, num, a);
                int size = a.size();
                gettimeofday(&start, NULL);
                for (int i = 0; i < size; ++i) {
                    quick_sort(a[i].begin(), a[i].end());
                }
                gettimeofday(&end, NULL);
                delta += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            }
            fprintf(data, "%d %.12f\n", j, delta / num);
        }
    } else if (strcmp(argv[1], "m") == 0) {
        fprintf(data, "MERGE SORT\n");
        for (int j = s; j < e; ++j) {
            cout << e-j << " more to go" << endl;
            int cur_pos = 0;
            vector<vector<int> > a;
            while (cur_pos < num) {
                get_shuffled_vectors(j, limit, cur_pos, num, a);
                int size = a.size();
                gettimeofday(&start, NULL);
                for (int i = 0; i < size; ++i) {
                    merge_sort(a[i].begin(), a[i].end());
                }
                gettimeofday(&end, NULL);
                delta += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            }
            fprintf(data, "%d %.12f\n", j, delta / num);
        }
    } else if (strcmp(argv[1], "i") == 0) {
        fprintf(data, "INSERTION SORT\n");
        for (int j = s; j < e; ++j) {
            cout << e-j << " more to go" << endl;
            int cur_pos = 0;
            vector<vector<int> > a;
            while (cur_pos < num) {
                get_shuffled_vectors(j, limit, cur_pos, num, a);
                int size = a.size();
                gettimeofday(&start, NULL);
                for (int i = 0; i < size; ++i) {
                    insertion_sort(a[i].begin(), a[i].end());
                }
                gettimeofday(&end, NULL);
                delta += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            }
            fprintf(data, "%d %.12f\n", j, delta / num);
        }
    } else if (strcmp(argv[1], "h") == 0) {
        fprintf(data, "HEAP SORT\n");
        for (int j = s; j < e; ++j) {
            cout << e-j << " more to go" << endl;
            int cur_pos = 0;
            vector<vector<int> > a;
            while (cur_pos < num) {
                get_shuffled_vectors(j, limit, cur_pos, num, a);
                int size = a.size();
                gettimeofday(&start, NULL);
                for (int i = 0; i < size; ++i) {
                    heap_sort(a[i].begin(), a[i].end());
                }
                gettimeofday(&end, NULL);
                delta += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            }
            fprintf(data, "%d %.12f\n", j, delta / num);
        }
    } else {
        cout << "Invalid argument #1! Got " << argv[1] << " expected q, h, m or i" << endl; return 0;
    }

    gettimeofday(&off, NULL);
    fprintf(data, "Done!\n");
    cout << "Time: " <<  (off.tv_sec - on.tv_sec) + (off.tv_usec - on.tv_usec) / 1000000.0 << "\nDone!" << endl;
    fclose(data);
    return 0;
}
