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

int main() {
    long long A;
    long long B;
    long long C;
    long long K;

    long long ans = 0;

    cin >> A >> B >> C >> K;

    long long minV = min(A, K);
    ans += minV;
    K -= minV;

    minV = min(B, K);
    K -= minV;

    minV = min(C, K);
    ans -= minV;

    cout << ans << endl;

    return 0;
}