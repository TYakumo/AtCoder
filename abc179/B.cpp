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

int main() {
    int N;
    cin >> N;

    VVI D(N, VI(2));
    bool ok = false;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> D[i][j];
        }

        if (i >= 2 && D[i][0] == D[i][1]) {
            if (D[i-2][0] == D[i-2][1]
            && D[i-1][0] == D[i-1][1]) {
                ok = true;
            }
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}