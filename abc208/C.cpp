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
    long long K;
    cin >> N >> K;

    VI A(N);
    VVI rank(N, VI(2));
    long long allGet = K/N;
    VLL ans(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        rank[i] = {A[i], i};
        ans[i] = allGet;
    }

    K %= N;
    sort(rank.begin(), rank.end());

    for (int i = 0; i < K; ++i) {
        ++ans[rank[i][1]];
    }

    for (int i = 0; i < N; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}