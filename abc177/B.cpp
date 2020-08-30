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
    string S;
    string T;
    cin >> S >> T;

    const int INF = 1000000;
    int ans = INF;

    for (int s = 0; s + T.size() <= S.size(); ++s) {
        int res = 0;
        for (int i = 0; i < T.size(); ++i) {
            if (T[i] != S[s+i]) {
                ++res;
            }
        }

        ans = min(ans, res);
    }

    cout << ans << endl;
    return 0;
}