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
const long long INF = 1000000000LL*1000000000LL;

long long solve(VLL A) {
    long long res = 0;

    if (A[1] < A[0]) {
        res += A[0]-A[1];
        A[1] = A[0];
    }

    if (A[2] < A[1]) {
        res += A[1]-A[2];
        A[2] = A[1];
    }

    long long delta1 = A[1]-A[0];
    long long delta2 = A[2]-A[0];

    if (delta2%2) {
        ++delta2;
        ++A[2];
        ++res;
    }

    long long hd = delta2/2;

    if (hd >= delta1) {
        res += (hd-delta1);
    } else {
        res += (delta1-hd)*2;
    }

    return res;
}

int main() {
    VLL A(3);
    for (int i = 0; i < 3; ++i) {
        cin >> A[i];
    }

    long long ans = solve(A);
    reverse(A.begin(), A.end());
    ans = min(ans, solve(A));

    cout << ans << endl;

    return 0;
}