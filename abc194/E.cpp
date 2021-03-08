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
using namespace std;

using VI = vector <int>;

int main() {
    int N;
    int M;
    cin >> N >> M;

    VI A(N);
    set <int> holes;
    unordered_map<int, int> cnt;
    for (int i = 0; i < N; ++i) {
        holes.insert(i);
        cin >> A[i];
    }

    holes.insert(N);
    // init
    const int INF = 1000000000;
    int ans = INF;

    for (int i = 0; i < M; ++i) {
        if (cnt[A[i]] == 0) {
            holes.erase(holes.find(A[i]));
        }
        ++cnt[A[i]];
    }

    ans = *holes.begin();

    for (int i = M; i < N; ++i) {
        // shifting
        --cnt[A[i-M]];

        if (cnt[A[i-M]] == 0) {
            holes.insert(A[i-M]);
        }

        if (cnt[A[i]] == 0) {
            holes.erase(holes.find(A[i]));
        }

        ++cnt[A[i]];

        ans = min(ans, *holes.begin());
    }

    cout << ans << endl;

    return 0;
}