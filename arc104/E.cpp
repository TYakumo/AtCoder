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

using PI = pair <int, int>;
using VPI = vector <PI>;
using VI = vector <int>;
using VVI = vector <VI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VVVLL = vector <VVLL>;
using UMLL = unordered_map<long long, int>;
const long long MOD = 1000000000 + 7;
const long long INF = 1000000000000000LL;

UMLL m;
UMLL mtoc;
VVVLL comb;

struct GCDInfo {
    long long x;
    long long y;
    long long g;
    GCDInfo(long long px, long long py, long long pg) : x(px), y(py), g(pg) {
    }
};

GCDInfo gcd(long long a, long long b) {
    if (b == 0) {
        return GCDInfo(1, 0, a);
    }

    // ax+by = g
    // bx'+(a-a/b*b)y' = g
    GCDInfo v = gcd(b, a%b);
    return GCDInfo(v.y, v.x-(a/b)*v.y, v.g);
}

// Get a * x mod p = 1
long long findInv(long long a, long long p) {
    return gcd(a, p).x;
}

void precalC(VVVLL& c, UMLL& coorMapper, int N) {
    int C = coorMapper.size();
    c = move(VVVLL(C, VVLL(C, VLL(N+1))));

    for (int i = 0; i < C; ++i) {
        for (int j = i+1; j < C; ++j) {
            long long s = coorMapper[i]+1;
            long long e = coorMapper[j];
            long long len = e-s+1;
            long long res = 1;

            // C(len k)
            for (int k = 0; k <= N && k <= len; ++k) {
                c[i][j][k] = res;
                res *= (len-k);
                res %= MOD;
                res *= findInv(k+1, MOD);
                res %= MOD;
            }
        }
    }
}

void buildMapper(VLL A, UMLL& mapper, UMLL& coorMapper) {
    int cnt = 0;
    sort(A.begin(), A.end());

    coorMapper[cnt] = 0;
    mapper[0] = cnt++; // default coordinate
    coorMapper[cnt] = A[0];
    mapper[A[0]] = cnt++;
    for (int i = 1; i < A.size(); ++i) {
        if (A[i] != A[i-1]) {
            coorMapper[cnt] = A[i];
            mapper[A[i]] = cnt++;
        }
    }
}

void fillIn(int n, bool used, int now, int remain, VI& order, VLL& A, long long& ans) {
    int N = A.size();

    if (remain == 0) {
        long long len = 1; // LIS length
        VLL best(N, 1);

        for (int i = 0; i < N; ++i) {
            for (int j = i-1; j >= 0; --j) {
                if (order[i] > order[j]) {
                    best[i] = max(best[i], best[j]+1);
                    len = max(len, best[i]);
                }
            }
        }

        int C = m.size();
        VPI VA;

        for (int i = 0; i < N; ++i) {
            VA.push_back(make_pair(order[i], i));
        }
        sort(VA.begin(), VA.end());

        VVLL dp(N+1, VLL(C+1));
        dp[0][0] = 1;

        VVLL endMin(N+1, VLL(N+1, INF));

        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j) {
                for (int k = i; k <= j; ++k) {
                    endMin[i][j] = min(endMin[i][j], A[VA[k].second]);
                }
            }
        }

        for (int n = 0; n <= N; ++n) {
            for (int c = 0; c < C-1; ++c) {
                if (dp[n][c]) {
                    dp[n][c+1] += dp[n][c]; // no Ai lies in this segment
                    dp[n][c+1] %= MOD;
                    int cho = 0;

                    for (int nn = n+1; nn <= N; ++nn) {
                        if (nn+1 <= N && VA[nn-1].first == VA[nn].first) { // must choose next one
                            continue;
                        }

                        ++cho;
                        long long end = mtoc[c+1];

                        if (endMin[n+1 - 1][nn - 1] >= end) { // to be converted to VA
                            dp[nn][c+1] += dp[n][c] * comb[c][c+1][cho];
                            dp[nn][c+1] %= MOD;
                        } else {
                            break;
                        }
                    }
                }
            }
        }

        ans += len * dp[N][C-1];
        ans %= MOD;
        return ;
    }

    if (now == N) {
        if (used) {
            fillIn(n+1, false, 0, remain, order, A, ans);
        }
        return ;
    }

    if (order[now] == 0) {
        order[now] = n;
        fillIn(n, true, now+1, remain-1, order, A, ans);
        order[now] = 0;
    }

    fillIn(n, used, now+1, remain, order, A, ans);
}

int main() {
    int N;

    cin >> N;

    VLL A(N);
    VI order(N);
    long long tot = 0;
    long long deno = 1;
    long long ans = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        deno *= A[i];
        deno %= MOD;
    }

    buildMapper(A, m, mtoc);
    precalC(comb, mtoc, N);
    fillIn(1, false, 0, N, order, A, tot);

    // tot / deno = ans mod M
    ans = (tot * findInv(deno, MOD)) % MOD;
    ans = (ans + MOD)%MOD;
    cout << ans << endl;

    return 0;
}