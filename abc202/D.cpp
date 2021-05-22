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
    int A;
    int B;
    long long K;
    cin >> A >> B >> K;

    int N = A+B;
    VVLL C(N+1, VLL(N+1));
    C[0][0] = 1;

    for (int i = 1; i <= N; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];;
        }
    }

    string ans;
    for (int l = 0; l < N && A > 0 && B > 0; ++l) {
        if (A > 0 && K <= C[A+B-1][A-1]) {
            ans += 'a';
            --A;
        } else {
            ans += 'b';
            K -= C[A+B-1][A-1];
            --B;
        }
    }

    while (A--) {
        ans += 'a';
    }

    while (B--) {
        ans += 'b';
    }

    cout << ans << endl;

    return 0;
}