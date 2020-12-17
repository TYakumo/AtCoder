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
#include <queue>
using namespace std;

using DI = deque <int>;

int main() {
    int N;
    int M;
    cin >> N >> M;

    DI A;
    int k = N;

    A.push_back(0);
    for (int i = 0; i < M; ++i) {
        int val;
        cin >> val;
        A.push_back(val);
    }
    A.push_back(N+1);
    sort(A.begin(), A.end());

    for (int i = 1; i < A.size(); ++i) {
        int len = A[i]-A[i-1]-1;

        if (len != 0) {
            k = min(k, len);
        }
    }

    int ans = 0;
    for (int i = 1; i < A.size(); ++i) {
        int len = A[i]-A[i-1]-1;

        if (len != 0) {
            int times = (len+k-1)/k;
            ans += times;
        }
    }

    cout << ans << endl;

    return 0;
}