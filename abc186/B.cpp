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

using VI = vector <int>;
using VVI = vector <VI>;

int main() {
    int H;
    int W;
    cin >> H >> W;

    int tot = 0;
    int minv = 1000000000;
    VVI A(H, VI(W));

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> A[i][j];
            minv = min(minv, A[i][j]);
        }
    }

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            tot += A[i][j]-minv;
        }
    }

    cout << tot << endl;

    return 0;
}