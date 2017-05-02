#include "mwc.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::string;

MWC readDIMACS(char * fname) {
    string s;
    int n;
    MWC mwc;
    ifstream fin(fname);
    if (! fin){ // IS THERE A WAY TO THROW AN IO EXCEPTION?
        cerr << "failed to open file named " << fname << endl;
        return mwc;
    }
    fin >> s; // p
    fin >> s; // edge
    fin >> n;
    vector<vector<int> > a(n, vector<int>(n, 0));
    vector<int> degree(n, 0);
    vector<weight_type> weight(n, 1);
    int u, v;
    while (fin) {
        fin >> s;
        if (s == "n") {
            fin >> v;
            fin >> weight[v - 1];
        }
        if (s == "e") {
            fin >> u;
            fin >> v;
            a[u - 1][v - 1] = a[v - 1][u - 1] = 1;
            degree[v - 1]++;
            degree[u - 1]++;
        }
    }
    fin.close();
    return MWC(n, a, degree, weight);
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

