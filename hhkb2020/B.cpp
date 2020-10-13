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

    cin >> H >> W;

    vector <string> S(H);
    for (int i = 0; i < H; ++i) {
        cin >> S[i];
    }

    int ans = 0;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (S[i][j] != '#') {
                if (j+1 < W && S[i][j+1] != '#') {
                    ++ans;
                }

                if (i+1 < H && S[i+1][j] != '#') {
                    ++ans;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}