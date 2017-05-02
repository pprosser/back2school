#include <iostream>
#include <vector>
#include <ctime>

using std::cout;
using std::endl;
using std::vector;

using namespace std;

class MWC {
    public:
        long nodes, maxWeight;
        clock_t cpuTime;
        int n;
        vector<vector<int> > A;
        vector<int> degree;
        vector<int> weight;
        vector<int> solution;

        MWC() {
            n = -1;
        }

        MWC(int n, vector<vector<int> > A, vector<int> degree, vector<int> weight) {
            this->n = n;
            this->A = A;
            this->degree = degree;
            this->weight = weight;
            nodes = 0;
            maxWeight = 0;
            vector<int> temp(n, 0);
            solution = temp;
        }

        void display() {
            cout << maxWeight << " " << nodes << " " << cpuTime * 1000 << endl;
            for (int i = 0 ; i < n ; i++)
                if (solution[i] == 1)
                    cout << i+1 << " ";
            cout << endl;
        }

        void search() {
            vector<int> P(n, 0);
            vector<int> C;
            long pWeight = 0;
            for (int i = 0 ; i < n ; i++) {
                P[i] = n - i - 1; // backwards, as in MWC.java
                pWeight = pWeight + weight[i]; // sum of all weights
            }
            cpuTime = time(0);
            expand(P, C, 0, pWeight);
            cpuTime = time(0) - cpuTime;
        }

        void save(vector<int> C, long currentWeight) {
            for (int i = 0 ; i < n ; i++)
                solution[i] = 0;
            for (int i = 0 ; i < C.size() ; i++)
                solution[C[i]] = 1;
            maxWeight = currentWeight;
        }

        void expand(vector<int> P, vector<int> C, long cWeight, long pWeight) {
            nodes++;
            int m = P.size();
            for (int i = m - 1 ; i >= 0 ; i--) {
                if (cWeight + pWeight <= maxWeight)
                    return;
                int v = P[i];
                C.push_back(v);
                vector<int> newP;
                long newPWeight = 0;
                for (int j = 0 ; j < i ; j++)
                    if (A[v][P[j]] == 1) {
                        newP.push_back(P[j]);
                        newPWeight = newPWeight + weight[P[j]];
                    }
                if (cWeight + weight[v] > maxWeight)
                    save(C,cWeight + weight[v]);
                if (! newP.empty())
                    expand(newP, C, cWeight + weight[v], newPWeight);
                C.pop_back();
                P.pop_back();
                pWeight = pWeight - weight[v];
            }
        }
        /*
         * Translation of MWC.java
         */
};
