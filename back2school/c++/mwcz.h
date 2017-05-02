#include <iostream>
#include <vector>
#include <ctime>

using std::cout;
using std::endl;
using std::vector;

using namespace std;

class MWCZ {
public:
  long nodes, maxWeight;
  long double cpuTime;
  int n;
  vector<vector<int> > A;
  vector<int> degree;
  vector<int> weight;
  vector<int> solution;
  vector<vector<int> > P; // candidate sets
  vector<int> C; // growing clique

  MWCZ(){n = -1;}

  MWCZ(int n,vector<vector<int> > A,vector<int> degree,vector<int> weight){
    this->n = n;
    this->A = A;
    this->degree = degree;
    this->weight = weight;
    nodes = 0;
    maxWeight = 0;
    vector<int> tempV(n,0); 
    solution = tempV;
    vector<vector<int> > tempP(n+1,vector<int>(0,0));
    P = tempP;
  }

  void display(){
    cout << maxWeight << " " << nodes << " " << cpuTime * 1000 << endl;
    for (int i=0;i<n;i++)
      if (solution[i] == 1) cout << i+1 << " ";
    cout << endl;
  }

  void search (){
    vector<int> C;
    long pWeight = 0;
    for (int i=0;i<n;i++){
      P[0].push_back(n - i - 1); // backwards, as in MWC.java
      pWeight = pWeight + weight[i]; // sum of all weights
    }
    cpuTime = time(0);
    expand(0,0,pWeight); 
    cpuTime = time(0) - cpuTime;
  }

  void save(vector<int> C,long currentWeight){
    for (int i=0;i<n;i++) solution[i] = 0;
    for (int i=0;i<C.size();i++) solution[C[i]] = 1;
    maxWeight = currentWeight;
  }

  void expand(int depth,long cWeight,long pWeight){
    nodes++;
    int m = P[depth].size();
    for (int i=m-1;i>=0;i--){
      if (cWeight + pWeight <= maxWeight) return;
      int v = P[depth][i];
      C.push_back(v);
      long newPWeight = 0;
      P[depth + 1].clear();
      for (int j=0;j<i;j++) 
	if (A[v][P[depth][j]] == 1){
	  P[depth + 1].push_back(P[depth][j]);
	  newPWeight = newPWeight + weight[P[depth][j]];
	}
      if (cWeight + weight[v] > maxWeight) save(C,cWeight + weight[v]);
      if (!P[depth+1].empty()) expand(depth+1,cWeight + weight[v],newPWeight);
      C.pop_back();
      pWeight = pWeight - weight[v];
    }
  }
  /*
   * Translation of MWC.java
   */
};
