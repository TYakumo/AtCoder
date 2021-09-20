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
    VI N(2);
    cin >> N[0] >> N[1];

    VVI A(2);

    for (int i = 0; i < 2; ++i) {
        A[i] = std::move(VI(N[i]));
        for (int j = 0; j < N[i]; ++j) {
            cin >> A[i][j];
        }
        sort(A[i].begin(), A[i].end());
    }

    int idx = 0;
    const int INF = 1000000000 + 100;
    int theMin = INF;

    for (int i = 0; i < N[0]; ++i) {
        while (idx < N[1] && A[0][i] > A[1][idx]) {
            ++idx;
        }

        if (idx < N[1]) {
            theMin = min(theMin, abs(A[0][i] - A[1][idx]));
        }

        if (idx-1 >= 0) {
            theMin = min(theMin, abs(A[0][i] - A[1][idx-1]));
        }
    }

    cout << theMin << endl;

    return 0;
}