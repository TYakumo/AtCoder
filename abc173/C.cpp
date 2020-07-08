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
    int H;
    int W;
    int K;
    cin >> H >> W >> K;

    vector <string> valRow(H);

    for (int i = 0; i < H; ++i) {
        cin >> valRow[i];
    }

    int rowCho = 1<<H;
    int colCho = 1<<W;

    // 2^6 * 2^6 * W*H = 4096 * 6 * 6
    int ans = 0;

    for (int rc = 0; rc < rowCho; ++rc) {
        for (int cc = 0; cc < colCho; ++cc) {
            vector <string> newRow(valRow.begin(), valRow.end());
            vector <bool> rowSet(H);
            vector <bool> colSet(W);

            const char RED = '.';

            for (int i = 0; i < H; ++i) {
                if (rc & (1<<i)) {
                    rowSet[i] = true;
                }
            }

            for (int i = 0; i < W; ++i) {
                if (cc & (1<<i)) {
                    colSet[i] = true;
                }
            }

            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) {
                    if (rowSet[i] || colSet[j]) {
                        newRow[i][j] = RED;
                    }
                }
            }

            int cnt = 0;
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) {
                    if (newRow[i][j] != RED) {
                        ++cnt;
                    }
                }
            }

            if (cnt == K) {
                ++ans;
            }
        }
    }

    cout << ans << endl;

    return 0;
}