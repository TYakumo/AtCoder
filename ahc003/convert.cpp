#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    const int MAXN = 30;
    const int TIMES = 1000;
    VVI V(MAXN, VI(MAXN));
    VVI H(MAXN, VI(MAXN));
    VLL sum(2);

    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN-1; ++j) {
            cin >> H[i][j];
            if (j) {
                cout << " ";
            }
            cout << H[i][j];
            sum[0] += H[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < MAXN-1; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            cin >> V[i][j];
            if (j) {
                cout << " ";
            }
            cout << V[i][j];
            sum[1] += H[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < TIMES; ++i) {
        VI p(5);
        for (int j = 0; j < 5; ++j) {
            cin >> p[j];
            if (j) {
                cout << " ";
            }
            cout << p[j];
        }
        double ratio;
        cin >> ratio;

        cout << " " << 1.0 << endl;
    }

    for (int i = 0; i < 2; ++i) {
        cerr << "AVG " << sum[i] / (MAXN-1) / MAXN << endl;
    }

    return 0;
}