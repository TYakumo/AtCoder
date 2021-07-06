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
using VUMI = vector <UMI>;
using UMLL = unordered_map<long long, long long>;
long long toIdx(int len, int two, int three, int five, int seven) {
    long long ret = len;
    ret = ret*128 + two;
    ret = ret*128 + three;
    ret = ret*128 + five;
    ret = ret*128 + seven;
    return ret;
}

inline long long mypow(long long n, long long p) {
    if (p == 0) {
        return 1;
    }

    long long half = mypow(n, p/2);
    long long mul = (n-1)*(p%2) + 1;

    return half * half * mul;
}


long long solve(UMLL &dp, int len, int two, int three, int five, int seven) {
    long long idx = toIdx(len, two, three, five, seven);

    if (len == 0 && two == 0 && three == 0 && five == 0 && seven == 0) {
        return 1;
    }

    if (len == 0) {
        return 0;
    }

    if (dp.count(idx)) {
        return dp[idx];
    }

    long long ret = 0;
    if (two >= 1) { // 2
        ret += solve(dp, len-1, two-1, three, five, seven);
    }

    if (two >= 2) { // 4
        ret += solve(dp, len-1, two-2, three, five, seven);
    }

    if (two >= 3) { // 8
        ret += solve(dp, len-1, two-3, three, five, seven);
    }

    if (three >= 1) { // 3
        ret += solve(dp, len-1, two, three-1, five, seven);
    }

    if (three >= 2) { // 9
        ret += solve(dp, len-1, two, three-2, five, seven);
    }

    if (two >= 1 && three >= 1) { // 6
        ret += solve(dp, len-1, two-1, three-1, five, seven);
    }

    if (five >= 1) { // 5
        ret += solve(dp, len-1, two, three, five-1, seven);
    }

    if (seven >= 1) { // 7
        ret += solve(dp, len-1, two, three, five, seven-1);
    }

    ret += solve(dp, len-1, two, three, five, seven); // 1
    return dp[idx] = ret;
}

long long getComb(UMLL &dp, int rlen, long long mul, long long K) {
    long long comb = 0;
    long long twoPow = mul;
    for (int two = 0; twoPow <= K; ++two) {
        long long threePow = twoPow;
        for (int three = 0; threePow <= K; ++three) {
            long long fivePow = threePow;
            for (int five = 0; fivePow <= K; ++five) {
                long long sevenPow = fivePow;
                for (int seven = 0; sevenPow <= K; ++seven) {
                    comb += solve(dp, rlen, two, three, five, seven);
                    sevenPow *= 7;
                }
                fivePow *= 5;
            }
            threePow *= 3;
        }
        twoPow *= 2;
    }

    return comb;
}

int main() {
    long long N;
    long long K;
    cin >> N >> K;
    VLL NL;

    while (N) {
        NL.push_back(N%10);
        N /= 10;
    }

    reverse(NL.begin(), NL.end());
    long long ans = 0;
    UMLL dp;

    long long mul = 1;
    for (int i = 0; i <= NL.size(); ++i) {
        if (i) {
            mul *= NL[i-1];
        }

        if (i == NL.size()) {
            if (mul <= K) {
                ++ans;
            }

            continue;
        }

        if (NL[i] >= 1) {
            int rlen = NL.size()-i-1;

            if (mul == 0) {
                long long comb = 0;
                for (int j = i; j < NL.size(); ++j) {
                    comb = comb*10 + NL[j];
                }
                ans += (comb+1);
                break;
            }

            if (i == 0) {
                for (int l = 1; l <= NL.size(); ++l) {
                    int upper = l == NL.size() ? NL[0]-1 : 9;
                    long long tot = 0;
                    int rl = l-1;
                    ans += (mypow(10, rl) - mypow(9, rl)) * upper;

                    for (int v = 1; v <= upper; ++v) {
                        ans += getComb(dp, rl, v, K);
                    }
                }

                continue;
            }

            // prod != 0
            for (int v = 1; v < NL[i]; ++v) {
                ans += getComb(dp, rlen, mul*v, K);
            }

            // prod = zero
            ans += mypow(10, rlen);
            ans += (mypow(10, rlen) - mypow(9, rlen)) * (NL[i]-1LL);
        }
    }

    cout << ans << endl;

    return 0;
}