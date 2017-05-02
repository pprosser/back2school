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

class MWC {
    public:
        long nodes, max_weight;
        milliseconds cpu_time;
        int n;
        vector<vector<int> > adjacency;
        vector<int> degree;
        vector<int> weight;
        vector<int> solution;

        MWC() :
            n(-1)
        {
        }

        MWC(int n, const vector<vector<int> > & adjacency, const vector<int> & degree, const vector<int> & weight) :
            nodes(0),
            max_weight(0),
            n(n),
            adjacency(adjacency),
            degree(degree),
            weight(weight),
            solution(n, 0)
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
            vector<int> p(n, 0);
            vector<int> c;
            long p_weight = 0;
            for (int i = 0 ; i < n ; i++) {
                p[i] = n - i - 1; // backwards, as in MWC.java
                p_weight += weight[i]; // sum of all weights
            }
            time_point<steady_clock> start_time = steady_clock::now();
            expand(p, c, 0, p_weight);
            cpu_time = duration_cast<milliseconds>(steady_clock::now() - start_time);
        }

        void save(const vector<int> & c, long current_weight) {
            solution.assign(n, 0);
            for (const auto & v : c)
                solution[v] = 1;
            max_weight = current_weight;
        }

        void expand(vector<int> & p, vector<int> & c, long c_weight, long p_weight) {
            nodes++;
            for (int i = p.size() - 1 ; i >= 0 ; i--) {
                if (c_weight + p_weight <= max_weight)
                    return;
                int v = p[i];
                c.push_back(v);
                vector<int> new_p;
                long new_p_weight = 0;
                for (int j = 0 ; j < i ; j++)
                    if (adjacency[v][p[j]] == 1) {
                        new_p.push_back(p[j]);
                        new_p_weight += weight[p[j]];
                    }
                if (c_weight + weight[v] > max_weight)
                    save(c, c_weight + weight[v]);
                if (! new_p.empty())
                    expand(new_p, c, c_weight + weight[v], new_p_weight);
                c.pop_back();
                p.pop_back();
                p_weight -= weight[v];
            }
        }
        /*
         * Translation of MWC.java
         */
};
