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
    int N;
    int K;
    cin >> N >> K;

    vector <int> P(N);
    vector <long long> C(N);

    for (int i = 0; i < N; ++i) {
        cin >> P[i];
        --P[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> C[i];
    }

    const long long INF = 1000000000LL * 1000000000LL;
    long long ans = -INF;
    vector <int> idx(N);
    vector <long long> acc(N);

    for (int i = 0; i < N; ++i) {
        int now = i;
        long long sum = 0;
        long long maxSum = -INF;
        long long cycleSum = 0;
        int cnt = 0;
        int cycleLength = 1;

        fill(idx.begin(), idx.end(), -1);
        fill(acc.begin(), acc.end(), 0);
        idx[now] = 0;
        acc[cnt] = sum;

        while (cnt < K) {
            now = P[now];
            if (idx[now] != -1) {
                // detect cycle
                cycleLength = (cnt+1) - idx[now];
                sum += C[now];
                cycleSum = idx[now] > 0 ? C[now] + acc[cnt] - acc[idx[now]-1] : C[now] + acc[cnt];
                maxSum = max(maxSum, sum);
                ++cnt;
                break;
            }

            sum += C[now];
            idx[now] = cnt++;
            acc[cnt] = sum;
            maxSum = max(maxSum, sum);
        }

        for (int s = 0; s < cycleLength && cnt < K; ++s) {
            now = P[now];
            sum += C[now];
            ++cnt;
            maxSum = max(maxSum, sum);
        }

        // loop sum
        int goStep = max(0, (K-cnt) / cycleLength - 1);
        sum += goStep * cycleSum;
        maxSum = max(maxSum, sum);

        int remain = K - cnt - goStep * cycleLength;

        for (int r = 0; r < remain; ++r) {
            now = P[now];
            sum += C[now];
            maxSum = max(maxSum, sum);
        }

        ans = max(ans, maxSum);
    }

    cout << ans << endl;

    return 0;
}