#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using VI = vector<int>;
const int MAXV = 300001;

int op(int a, int b) { return max(a, b); }

int e() { return 0; }

int main() {
    int N;
    int K;

    cin >> N >> K;

    segtree<int, op, e> seg(MAXV+10);

    int ans = 0;

    for (int i = 0; i < N; ++i) {
        int A;
        cin >> A;
        int best = seg.prod(max(0, A-K), min(MAXV, A+K)+1);
        ans = max(ans, best+1);
        seg.set(A, best+1);
    }

    cout << ans << endl;

    return 0;
}