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
    int N;
    int M;
    cin >> N >> M;

    VVVI V(N+1);
    // N*(2^N)
    int S = 1 << N;
    VVLL dp(N+1, VLL(S));
    dp[0][0] = 1;

    for (int i = 0; i < M; ++i) {
        int x;
        int y;
        int z;
        cin >> x >> y >> z;
        V[x].push_back({y, z});
    }

    for (int n = 1; n <= N; ++n) {
        for (int s = 0; s < S; ++s) {
            if (dp[n-1][s] == 0) {
                continue;
            }

            VI cho(N+1);
            VI acc(N+1);

            for (int i = 1; i <= N; ++i) {
                if ((1<<(i-1)) & s) {
                    ++cho[i];
                }
            }

            for (int nv = 1; nv <= N; ++nv) {
                if (((1<<(nv-1)) & s) == 0) {
                    int ns = (1<<(nv-1)) | s;
                    bool ok = true;
                    acc = cho;
                    ++acc[nv];

                    for (int i = 1; i <= N; ++i) {
                        acc[i] += acc[i-1];
                    }

                    for (int j = 0; j < V[n].size(); ++j) {
                        if (V[n][j][1] < acc[V[n][j][0]]) {
                            ok = false;
                            break;
                        }
                    }

                    if (ok) {
                        dp[n][ns] += dp[n-1][s];
                    }
                }
            }
        }
    }

    cout << dp[N][S-1] << endl;
    return 0;
}