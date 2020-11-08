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

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;

int findNext(VI& BLK, int cur) { // find first BLK[ret] > cur
    int low = 0;
    int up = BLK.size()-1;
    int ret = -1;

    while (low <= up) {
        int mid = (low+up) / 2;

        if (BLK[mid] > cur) {
            ret = BLK[mid];
            up = mid-1;
        } else {
            low = mid+1;
        }
    }

    return ret;
}

int findPrev(VI& BLK, int cur) { // find first BLK[ret] < cur
    int low = 0;
    int up = BLK.size()-1;
    int ret = -1;

    while (low <= up) {
        int mid = (low+up) / 2;

        if (BLK[mid] < cur) {
            low = mid+1;
            ret = BLK[mid];
        } else {
            up = mid-1;
        }
    }

    return ret;
}

int main() {
    int H;
    int W;

    cin >> H >> W;

    int N;
    int M;
    cin >> N >> M;

    VI A(N);
    VI B(N);

    VI C(M);
    VI D(M);
    VVI CBLK(H);
    VVI RBLK(W);
    VVI grid(H, VI(W));

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        --A[i];
        --B[i];
        grid[A[i]][B[i]] = 1;
        RBLK[B[i]].push_back(A[i]);
        CBLK[A[i]].push_back(B[i]);
    }

    for (int i = 0; i < M; ++i) {
        cin >> C[i] >> D[i];
        --C[i];
        --D[i];
        grid[C[i]][D[i]] = -1;
        RBLK[D[i]].push_back(C[i]);
        CBLK[C[i]].push_back(D[i]);
    }

    for (int i = 0; i < H; ++i) {
        sort(CBLK[i].begin(), CBLK[i].end());
    }

    for (int i = 0; i < W; ++i) {
        sort(RBLK[i].begin(), RBLK[i].end());
    }

    int ans = 0;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (grid[r][c] == 1) {
                ++ans;
            } else if (grid[r][c] == 0) {
                int nextIdx = findNext(RBLK[c], r);

                if (nextIdx != -1 && grid[nextIdx][c] == 1) {
                    ++ans;
                    continue;
                }

                nextIdx = findNext(CBLK[r], c);
                if (nextIdx != -1 && grid[r][nextIdx] == 1) {
                    ++ans;
                    continue;
                }

                int prevIdx = findPrev(RBLK[c], r);
                if (prevIdx != -1 && grid[prevIdx][c] == 1) {
                    ++ans;
                    continue;
                }

                prevIdx = findPrev(CBLK[r], c);
                if (prevIdx != -1 && grid[r][prevIdx] == 1) {
                    ++ans;
                    continue;
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}