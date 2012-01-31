#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

#define INSERTION 0
#define QUICK 1
#define HEAP 2
#define MERGE 3
#define INF (-1)

typedef std::vector<std::pair<char, int> > conf_t;

std::string write_conf(const conf_t& conf)
{
    std::stringstream str;
    for (size_t i = 0; i < conf.size(); ++i) {
        str << ":" << conf[i].first << " --> " << conf[i].second << ";";
    }
    return str.str();
}

int min_idx(const std::vector<int> & a) {
    int m = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != INF) {
            m = i; break;
        }
    }
    /* m is first non-inf here, except if all inf */
    for (int i = m + 1; i < a.size(); ++i) {
        if (a[i] < a[m] && a[i] != INF) {
            m = i;
        }
    }

    return m;
}

int main() {
    std::vector<char> legend(4);
    legend[INSERTION] = 'i';
    legend[QUICK]     = 'q';
    legend[HEAP]      = 'h';
    legend[MERGE]     = 'm';

    std::vector<std::vector<int> > graph;
    graph.resize(4);
    for (int i = 0; i < graph.size(); ++i) {
        graph[i].resize(4, INF);
    }

    ////////// MAKING GRAPH //////////
    graph[HEAP][INSERTION] = 300;
    graph[HEAP][QUICK] = 600;
    graph[HEAP][MERGE] = 600;
    graph[INSERTION][QUICK] = 400;
    graph[INSERTION][MERGE] = 400;
    graph[QUICK][MERGE] = 900;
    //////////////////////////////////


    /** cout graph **/
    for (int i = 0; i < legend.size(); ++i) { std::printf("   %c  ", legend[i]); }
    std::printf("\n");
    for (int i = 0; i < graph.size(); ++i) {
        std::printf("%c ", legend[i]);
        for (int j = 0; j < graph[i].size(); j++) {
            std::printf("% 5d", graph[i][j]);
        }
        std::printf("\n");
    }

    ////////////  MAKING CONF  //////////////
    /* find start */
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

    /* follow minimum */
    conf_t path;
    int c = 1, idx;
    while (c < graph.size()) {
        printf("root: %d, line: %d, idx: %d\n", root, root, idx);
        idx = min_idx(graph[root]);
        if (graph[root][idx] != INF) {
            path.push_back(std::make_pair(legend[root], graph[root][idx]));
            root = idx;
        }
        ++c;
    }
    path.push_back(std::make_pair(legend[root], -1));

    printf("%s\n", write_conf(path).c_str());
    return 0;
}
