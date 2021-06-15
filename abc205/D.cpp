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
    int Q;
    cin >> N >> Q;

    VLL A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    const long long UPPER = 1000000000LL * 1000000000LL + 1000000LL;
    for (int q = 0; q < Q; ++q) {
        long long target;
        cin >> target;

        long long low = 1;
        long long up = UPPER;
        long long ans = UPPER;

        while (low <= up) {
            long long mid = (low+up)/2;
            long long rank = mid;
            auto iter = upper_bound(A.begin(), A.end(), mid);

            rank -= (iter-A.begin());

            if (rank == target) {
                ans = mid;
                up = mid-1;
            } else if (rank < target) {
                low = mid+1;
            } else {
                up = mid-1;
            }
        }

        cout << ans << endl;
    }

    return 0;
}