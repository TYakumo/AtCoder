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

inline int charToInt(char ch) {
    switch (ch) {
        case 'A': return 0;
        case 'T': return 1;
        case 'C': return 2;
        default: return 3;
    }
}

int main() {
    int N;
    string S;
    cin >> N >> S;

    int ans = 0;
    VVI sum(S.size()+5, VI(4, 0));

    for (int i = 1; i <= S.size(); ++i) {
        char ch = S[i-1];
        sum[i] = sum[i-1];
        ++sum[i][charToInt(ch)];
    }

    for (int i = 1; i <= S.size(); ++i) {
        for (int j = i; j <= S.size(); ++j) {
            VI res(4);

            for (int k = 0; k < 4; ++k) {
                res[k] = sum[j][k] - sum[i-1][k];
            }

            bool ok = (res[0] == res[1]) && (res[2] == res[3]);

            if (ok) {
                ++ans;
            }
        }
    }

    cout << ans << endl;

    return 0;
}