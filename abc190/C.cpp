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

    VI A(M);
    VI B(M);

    // (Ai and Bi) and ....
    for (int i = 0; i < M; ++i) {
        cin >> A[i] >> B[i];
        --A[i];
        --B[i];
    }

    int K;
    cin >> K;
    VI C(K);
    VI D(K);

    for (int i = 0; i < K; ++i) {
        cin >> C[i] >> D[i];
        --C[i];
        --D[i];
    }

    int tot = 1<<K;
    int ans = 0;
    for (int st = 0; st < tot; ++st) {
        VI res(N);
        for (int i = 0; i < K; ++i) {
            int flag = 1<<i;
            if (st & flag) {
                ++res[D[i]];
            } else {
                ++res[C[i]];
            }
        }

        int ok = 0;
        for (int i = 0; i < M; ++i) {
            if (res[A[i]] > 0 && res[B[i]] > 0) {
                ++ok;
            }
        }

        ans = max(ans, ok);
    }

    cout << ans << endl;

    return 0;
}