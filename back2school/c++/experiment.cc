#include "mwc.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using namespace std;

MWC readDIMACS(char * fname) {
    string s;
    int n;
    MWC mwc;
    ifstream fin(fname);
    if (! fin.is_open()){ // IS THERE A WAY TO THROW AN IO EXCEPTION?
        cerr << "failed to open file named " << fname << endl;
        return mwc;
    }
    fin >> s; // p
    fin >> s; // edge
    fin >> n;
    vector<vector<int> > A(n, vector<int>(n, 0));
    vector<int> degree(n, 0);
    vector<int> weight(n, 1);
    int u, v;
    while (! fin.eof()) {
        fin >> s;
        if (s == "n") {
            fin >> v;
            fin >> weight[v - 1];
        }
        if (s == "e") {
            fin >> u;
            fin >> v;
            A[u - 1][v - 1] = A[v - 1][u - 1] = 1;
            degree[v - 1]++;
            degree[u - 1]++;
        }
    }
    fin.close();
    return MWC(n, A, degree, weight);
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " dimacsFile " << endl;
        return EXIT_FAILURE;
    }
    MWC mwc = readDIMACS(argv[1]);
    mwc.search();
    mwc.display();
    return EXIT_SUCCESS;
}

