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
using VVVLL = vector <VVLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int N;
    int M;
    int A;
    int B;
    cin >> N >> M;

    const long long INF = 1000000000LL;
    VVVLL dist(N+1, VVLL(N, VLL(N, INF)));

    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            dist[k][i][i] = 0;
        }
    }

    for (int i = 0; i < M; i++) {
        int A;
        int B;
        long long C;
        cin >> A >> B >> C;

        --A;
        --B;

        dist[0][A][B] = min(dist[0][A][B], C);
    }

    for (int k = 0; k < N; ++k) {
        dist[k+1] = dist[k];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                dist[k+1][i][j] = min(dist[k+1][i][j], dist[k][i][k] + dist[k][k][j]);
            }
        }
    }

    long long ans = 0;

    for (int k = 1; k <= N; ++k) {
        for (int s = 0; s < N; ++s) {
            for (int t = 0; t < N; ++t) {
                if (dist[k][s][t] < INF) {
                    ans += dist[k][s][t];
                }
            }
        }
    }

    cout << ans << endl;


    return 0;
}