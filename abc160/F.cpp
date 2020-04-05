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

vector <long long> comb;
vector <long long> ans;
vector <int> treeSize;
const int MOD = 1000000007;
vector <long long> fact;
vector <long long> factInv;

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

void solveComb(vector< vector<int> >& adja, int now, int parent) {
    treeSize[now] = 1;
    comb[now] = 1;

    // comb(now) = fact(treeSize-1) * PI comb(subTree) / PI (fact(|subtree|))
    int N = adja.size();
    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (nextv != parent) {
            solveComb(adja, nextv, now);
            comb[now] = (comb[now] * comb[nextv]) % MOD;
            comb[now] = (comb[now] * factInv[treeSize[nextv]]) % MOD;
            treeSize[now] += treeSize[nextv];
        }
    }

    comb[now] = (comb[now] * fact[treeSize[now]-1]) % MOD;
    comb[now] = (comb[now] + MOD) % MOD;
}

void solveAns(vector< vector<int> >& adja, int now, int parent) {
    // comb(now) = fact(treeSize-1) * PI comb(subTree) / PI (fact(|subtree|))
    int N = adja.size();
    ans[now] = (fact[N-1] * comb[now])%MOD;
    ans[now] = (ans[now] * factInv[treeSize[now]-1])%MOD;

    if (parent != -1) {
        int cpTreeSize = N - treeSize[now];
        ans[now] = (ans[now] * factInv[cpTreeSize]) % MOD;

        long long cpComb = ans[parent];
        cpComb = (cpComb * factInv[N-1]) % MOD;
        cpComb = (cpComb * fact[cpTreeSize-1]) % MOD;

        cpComb = (cpComb * fact[treeSize[now]]) % MOD;
        cpComb = (cpComb * gcd(comb[now], MOD).x) % MOD; // avoid comb[now] to be negative (g < 0)

        ans[now] = (ans[now] * cpComb) % MOD;
    }

    ans[now] = (ans[now] + MOD) % MOD;

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (nextv != parent) {
            solveAns(adja, nextv, now);
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    comb = move(vector<long long>(N));
    ans = move(vector<long long>(N));
    treeSize = move(vector<int>(N));

    vector< vector<int> > adja(N);
    vector<int> dp(N, 1);

    for (int i = 1; i < N; ++i) {
        int f;
        int t;
        scanf("%d %d", &f, &t);
        --f;
        --t;

        adja[f].push_back(t);
        adja[t].push_back(f);
    }

    fact = move(vector<long long>(N+1));
    factInv = move(vector<long long>(N+1));

    fact[0] = 1;
    factInv[0] = (gcd(fact[0], MOD).x + MOD) % MOD;

    for (int i = 1; i <= N; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
        factInv[i] = (gcd(fact[i], MOD).x + MOD) % MOD;
    }

    solveComb(adja, 0, -1);
    solveAns(adja, 0, -1);

    for (int i = 0; i < N; ++i) {
        long long res = (ans[i]+MOD)%MOD;
        printf("%lld\n", res);
    }

    return 0;
}