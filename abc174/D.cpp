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
    int N;
    int ans = 0;
    string S;
    cin >> N >> S;

    int W = 0;
    int R = 0;

    for (int i = 0; i < N; ++i) {
        if (S[i] == 'R') {
            ++R;
        } else {
            ++W;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (i < R) {
            if (S[i] == 'W') { // should be swapped
                ++ans;
            }
        }
    }

    cout << ans << endl;

    return 0;
}