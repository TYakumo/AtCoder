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

int best(const VI& A, int now, int cache, int res) {
    if (now == A.size()) {
        return res^cache;
    }

    const int INF = 2000000000;
    int ret = INF;
    if (cache != 0) { // try to flush
        ret = best(A, now, 0, res^cache);
    }

    ret = min(ret, best(A, now+1, cache | A[now], res));
    return ret;
}

int main() {
    int N;
    cin >> N;

    VI A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    cout << best(A, 0, 0, 0) << endl;

    return 0;
}