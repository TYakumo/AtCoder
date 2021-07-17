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

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

int main() {
    long long N;
    int M;
    cin >> N >> M;

    VVLL A(M, VLL(2));
    long long g = N;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> A[i][j];
        }
        g = gcd(g, A[i][0]);
        swap(A[i][0], A[i][1]);
    }

    sort(A.begin(), A.end());

    if (g != 1) {
        cout << -1 << endl;
    } else {
        long long nowg = N;
        long long ans = 0;

        for (int i = 0; i < M && nowg != 1; ++i) {
            long long ng = gcd(nowg, A[i][1]);

            if (ng != nowg) {
                long long diff = (nowg-ng);
                ans += diff * A[i][0];
                nowg = ng;
            }
        }

        cout << ans << endl;
    }

    return 0;
}