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

using VS = vector <string>;
using VI = vector <int>;
using VVI = vector <VI>;

const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};

void solve(const VS& arr, VVI& used, int r, int c, int pred, int& ans) {
    int H = arr.size();
    int W = arr[0].size();
    bool failedToGo = false;

    used[r][c] = 1;

    if (pred != -1) {
        int ndr = dr[pred] + r;
        int ndc = dc[pred] + c;

        if (ndr >= 0 && ndr < H
            && ndc >= 0 && ndc < W) {
            if (arr[ndr][ndc] == '#') {
                if (used[ndr][ndc] == 0) {
                    solve(arr, used, ndr, ndc, pred, ans);
                }
            } else {
                failedToGo = true;
            }
        } else {
            failedToGo = true;
        }
    } else {
        failedToGo = true;
    }

    if (failedToGo) {
        int ok = 0;

        for (int dir = 0; dir < 4; ++dir) {
            if (dir != pred) {
                int ndr = dr[dir] + r;
                int ndc = dc[dir] + c;

                if (ndr >= 0 && ndr < H
                && ndc >= 0 && ndc < W) {
                    if (arr[ndr][ndc] == '#' && used[ndr][ndc] == 0) {
                        solve(arr, used, ndr, ndc, dir, ans);
                        ++ans;
                        ++ok;
                    }
                }
            }
        }
    }
}

void expand(VS& arr) {
    int H = arr.size();
    int W = arr[0].size();
    VS newarr(3*H, string(W*3, '.'));

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (arr[i][j] == '#') {
                int br = i*3;
                int bc = j*3;
                for (int a = 0; a < 3; ++a) {
                    for (int b = 0; b < 3; ++b) {
                        newarr[br+a][bc+b] = '#';
                    }
                }
            }
        }
    }

    arr = newarr;
}

int main() {
    int H;
    int W;

    cin >> H >> W;

    VS arr(H);

    for (int i = 0; i < H; ++i) {
        cin >> arr[i];
    }

    expand(arr);

    H = arr.size();
    W = arr[0].size();
    VVI used(H, VI(W));
    VVI cnt(H, VI(W));

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            for (int d = 0; d < 4; ++d) {
                int nr = dr[d] + i;
                int nc = dc[d] + j;

                if (nr >= 0 && nr < H
                && nc >= 0 && nc < W
                && arr[nr][nc] == '#') {
                    ++cnt[i][j];
                }
            }
        }
    }

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {

            if (cnt[i][j] == 4) {
                arr[i][j] = '.';
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (arr[i][j] == '#') {
                solve(arr, used, i, j, -1, ans);
            }
        }
    }

    cout << ans << endl;

    return 0;
}