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
    int N;
    cin >> N;

    VVI A(3, VI(N));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    long long ans = 0;
    UMLL cnt;
    for (int i = 0; i < N; ++i) {
        int C = A[2][i];
        int B = A[1][C-1];
        ++cnt[B];
    }

    for (int i = 0; i < N; ++i) {
        ans += cnt[A[0][i]];
    }

    cout << ans << endl;

    return 0;
}