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

    VLL A(N);
    UMLL cnt(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        ++cnt[A[i]];
    }

    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        long long comb = N - cnt[A[i]];
        ans += comb;
    }

    cout << ans/2 << endl;

    return 0;
}