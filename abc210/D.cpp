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
    int H;
    int W;
    long long C;
    cin >> H >> W >> C;

    VVVLL A(4, VVLL(H, VLL(W)));
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            cin >> A[0][r][c];
            A[1][r][W-1-c] = A[0][r][c];
        }
    }

    for (int r = 0; r < H; ++r) {
        A[2][H-1-r] = A[0][r];
        A[3][H-1-r] = A[1][r];
    }

    const long long INF = 1000000000LL * 1000000LL;
    VVVLL CHO(4, VVLL(H, VLL(W, INF)));
    VVVLL DP(4, VVLL(H, VLL(W, INF)));

    for (int d = 0; d < 4; ++d) {
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                long long sum = A[d][r][c]+C;
                if (r > 0) {
                    CHO[d][r][c] = min(CHO[d][r][c], CHO[d][r-1][c]+C);
                    CHO[d][r][c] = min(CHO[d][r][c], A[d][r-1][c]+C);
                }

                if (c > 0) {
                    CHO[d][r][c] = min(CHO[d][r][c], CHO[d][r][c-1]+C);
                    CHO[d][r][c] = min(CHO[d][r][c], A[d][r][c-1]+C);
                }

                DP[d][r][c] = min(DP[d][r][c], CHO[d][r][c]+A[d][r][c]);
            }
        }
    }

    long long ans = INF;

    for (int d = 0; d < 4; ++d) {
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                ans = min(ans, DP[d][r][c]);
            }
        }
    }

    cout << ans << endl;
    return 0;
}