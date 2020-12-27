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
#include <algorithm>
#include <functional>
using namespace std;

using VI = vector <int>;
using VS = vector <string>;
using VVI = vector <VI>;
using VLL = vector <long long>;
const long long MOD = 1000000000LL + 7;

inline long long modpow(long long n, long long p) {
    if (p == 0) {
        return 1;
    }

    long long half = modpow(n, p/2);
    long long mul = (n-1)*(p%2) + 1;

    return half * half % MOD * mul % MOD;
}

int main() {
    int N;
    cin >> N;

    string AA;
    string AB;
    string BA;
    string BB;

    cin >> AA >> AB >> BA >> BB;

    VLL dp(N+1);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= N; ++i) {
        dp[i] = (dp[i-1] + dp[i-2])%MOD;
    }

    if (N <= 3) {
        cout << 1 << endl;
    } else {
        if (AB == "B") {
            // AB => B, ABB
            // BB = B => 1
            if (BB == "B") {
                cout << 1 << endl;
            } else {
                // ABB => ABAB
                if (BA == "A") {
                    // ABBBBB => insert any A => AB***B
                    cout << modpow(2, N-3) << endl;
                } else {
                    // ABAB => ABBAB or ABABB => any string but no AA
                    // xxxxB or xxxxxBA => F(n-1) + F(n-2)
                    cout << dp[N-2] << endl;
                }
            }
        } else { //AAB
            if (AA == "A") { // AAB => AAAB
                cout << 1 << endl;
            } else {
                // AAB => ABAB
                if (BA == "B") {
                    // AAAAAB => insert any B => A***AB
                    cout << modpow(2, N-3) << endl;
                } else {
                    // ABAB => ABBAB or ABABB => any string but no AA
                    // xxxxB or xxxxxBA => F(n-1) + F(n-2)
                    cout << dp[N-2] << endl;
                }
            }
        }
    }


    return 0;
}