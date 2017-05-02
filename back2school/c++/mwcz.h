#include <iostream>
#include <vector>
#include <chrono>

using std::cout;
using std::endl;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::steady_clock;
using std::chrono::milliseconds;
using std::chrono::time_point;

class MWCZ {
    public:
        long nodes, max_weight;
        milliseconds cpu_time;
        int n;
        vector<vector<int> > adjacency;
        vector<int> degree;
        vector<int> weight;
        vector<int> solution;
        vector<vector<int> > p; // candidate sets
        vector<int> c; // growing clique

        MWCZ() :
            n(-1)
        {
        }

        MWCZ(int n, const vector<vector<int> > & adjacency, const vector<int> & degree, const vector<int> & weight) :
            nodes(0),
            max_weight(0),
            n(n),
            adjacency(adjacency),
            degree(degree),
            weight(weight),
            solution(n, 0),
            p(n + 1, vector<int>(0, 0))
        {
        }

        void display() {
            cout << max_weight << " " << nodes << " " << cpu_time.count() << endl;
            for (int i = 0 ; i < n ; i++)
                if (solution[i] == 1)
                    cout << i + 1 << " ";
            cout << endl;
        }

        void search() {
            long p_weight = 0;
            for (int i = 0 ; i < n ; i++) {
                p[0].push_back(n - i - 1); // backwards, as in MWC.java
                p_weight = p_weight + weight[i]; // sum of all weights
            }

            time_point<steady_clock> start_time = steady_clock::now();
            expand(0, 0, p_weight);
            cpu_time = duration_cast<milliseconds>(steady_clock::now() - start_time);
        }

        void save(const vector<int> & c, long current_weight) {
            solution.assign(n, 0);
            for (int i = 0 ; i < c.size() ; i++)
                solution[c[i]] = 1;
            max_weight = current_weight;
        }

        void expand(int depth, long c_weight, long p_weight) {
            nodes++;
            int m = p[depth].size();
            for (int i = m - 1 ; i >= 0 ; i--) {
                if (c_weight + p_weight <= max_weight)
                    return;
                int v = p[depth][i];
                c.push_back(v);
                long new_p_weight = 0;
                p[depth + 1].clear();
                for (int j = 0 ; j < i ; j++)
                    if (adjacency[v][p[depth][j]] == 1) {
                        p[depth + 1].push_back(p[depth][j]);
                        new_p_weight = new_p_weight + weight[p[depth][j]];
                    }
                if (c_weight + weight[v] > max_weight)
                    save(c, c_weight + weight[v]);
                if (! p[depth+1].empty())
                    expand(depth + 1, c_weight + weight[v], new_p_weight);
                c.pop_back();
                p_weight = p_weight - weight[v];
            }
        }
        /*
         * Translation of MWC.java
         */
};
