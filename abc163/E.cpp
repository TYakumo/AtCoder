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

using VVL = vector< vector <long long> >;
using VP = vector < pair<long long, int> >;

long long solve(VVL& dp, VP& cho, int now, int used) {
    if (now == cho.size()) {
        return 0;
    }

    if (dp[now][used] >= 0) {
        return dp[now][used];
    }

    int N = cho.size();

    // to left
    // N-used-1 - left == N - now-1
    // left = now-used
    int left = now-used;
    long long gain = abs(left-cho[now].second) * cho[now].first;
    dp[now][used] = max(dp[now][used], solve(dp, cho, now+1, used) + gain);

    // to right
    int right = N-used-1;
    gain = abs(right-cho[now].second) * cho[now].first;
    dp[now][used] = max(dp[now][used], solve(dp, cho, now+1, used+1) + gain);

    return dp[now][used];
}

int main() {
    int N;
    cin >> N;

    vector <long long> A(N);
    VP cho(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        cho[i] = make_pair(A[i], i);
    }

    sort(cho.begin(), cho.end(), greater<pair<long long, int>>());

    VVL dp(N+1, vector<long long>(N+1, -1));

    cout << solve(dp, cho, 0, 0) << endl;

    return 0;
}