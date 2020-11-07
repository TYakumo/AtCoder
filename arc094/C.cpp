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
    VI A(3);

    for (int i = 0; i < 3; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    int d = A[2] - A[1];
    int ans = d;

    A[0] += d;
    A[1] += d;

    d = A[1]-A[0];
    ans += d/2;
    A[0] += d/2*2;

    if (A[0] != A[1]) {
        ans += 2;
    }

    cout << ans << endl;

    return 0;
}