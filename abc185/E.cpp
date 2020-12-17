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
#include <unordered_map>
using namespace std;

using UMI = unordered_map<int, int>;
using VI = vector <int>;
using VVI = vector <VI>;

int main() {
    int N;
    int M;
    cin >> N >> M;

    VI A(N);
    VI B(M);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    for (int i = 0; i < M; ++i) {
        cin >> B[i];
    }

    VVI DP(N+1, VI(M+1));
    const int INF = 1000000000;

    for (int i = 0; i <= N; ++i) {
        DP[i][0] = i;
    }

    for (int i = 0; i <= M; ++i) {
        DP[0][i] = i;
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            int Aval = A[i-1];
            int Bval = B[j-1];
            DP[i][j] = INF;

            if (Aval == Bval) {
                DP[i][j] = DP[i-1][j-1];
            } else {
                DP[i][j] = min(DP[i][j], min(DP[i][j-1], DP[i-1][j])+1);
                DP[i][j] = min(DP[i][j], DP[i-1][j-1]+1);
            }
        }
    }

    cout <<  DP[N][M] << endl;

    return 0;
}