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

int main() {
    int H;
    int W;
    int X;
    int Y;
    cin >> H >> W;
    cin >> X >> Y;

    VS str(H);

    for (int i = 0; i < H; ++i) {
        cin >> str[i];
    }

    --X;
    --Y;

    const int dr[] = {1, -1, 0, 0};
    const int dc[] = {0, 0, 1, -1};

    int ans = 1;

    for (int dir = 0; dir < 4; ++dir) {
        int nr = X+dr[dir];
        int nc = Y+dc[dir];

        while (nr >= 0 && nr < H
            && nc >= 0 && nc < W
            && str[nr][nc] == '.') {
            ++ans;
            nr += dr[dir];
            nc += dc[dir];
        }
    }

    cout << ans << endl;


    return 0;
}