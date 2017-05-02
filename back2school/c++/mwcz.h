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
        long nodes, maxWeight;
        milliseconds cpuTime;
        int n;
        vector<vector<int> > A;
        vector<int> degree;
        vector<int> weight;
        vector<int> solution;
        vector<vector<int> > P; // candidate sets
        vector<int> C; // growing clique

        MWCZ() :
            n(-1)
        {
        }

        MWCZ(int n, const vector<vector<int> > & A, const vector<int> & degree, const vector<int> & weight) :
            nodes(0),
            maxWeight(0),
            n(n),
            A(A),
            degree(degree),
            weight(weight),
            solution(n, 0),
            P(n + 1, vector<int>(0, 0))
        {
        }

        void display() {
            cout << maxWeight << " " << nodes << " " << cpuTime.count() << endl;
            for (int i = 0 ; i < n ; i++)
                if (solution[i] == 1)
                    cout << i + 1 << " ";
            cout << endl;
        }

        void search() {
            vector<int> C;
            long pWeight = 0;
            for (int i = 0 ; i < n ; i++) {
                P[0].push_back(n - i - 1); // backwards, as in MWC.java
                pWeight = pWeight + weight[i]; // sum of all weights
            }

            time_point<steady_clock> start_time = steady_clock::now();
            expand(0, 0, pWeight);
            cpuTime = duration_cast<milliseconds>(steady_clock::now() - start_time);
        }

        void save(const vector<int> & C, long currentWeight) {
            for (int i = 0 ; i < n ; i++)
                solution[i] = 0;
            for (int i = 0 ; i < C.size() ; i++)
                solution[C[i]] = 1;
            maxWeight = currentWeight;
        }

        void expand(int depth, long cWeight, long pWeight) {
            nodes++;
            int m = P[depth].size();
            for (int i = m - 1 ; i >= 0 ; i--) {
                if (cWeight + pWeight <= maxWeight)
                    return;
                int v = P[depth][i];
                C.push_back(v);
                long newPWeight = 0;
                P[depth + 1].clear();
                for (int j = 0 ; j < i ; j++)
                    if (A[v][P[depth][j]] == 1) {
                        P[depth + 1].push_back(P[depth][j]);
                        newPWeight = newPWeight + weight[P[depth][j]];
                    }
                if (cWeight + weight[v] > maxWeight)
                    save(C, cWeight + weight[v]);
                if (! P[depth+1].empty())
                    expand(depth + 1, cWeight + weight[v], newPWeight);
                C.pop_back();
                pWeight = pWeight - weight[v];
            }
        }
        /*
         * Translation of MWC.java
         */
};
