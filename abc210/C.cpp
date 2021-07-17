#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int N;
    int K;
    cin >> N >> K;

    VI c(N);
    for (int i = 0; i < N; ++i) {
        cin >> c[i];
    }

    UMI cnt;

    int ans = 0;
    int tot = 0;
    int j = 0;
    for (int i = 0; i < N; ++i) {
        if (i) {
            --cnt[c[i-1]];
            if (cnt[c[i-1]] == 0) {
                --tot;
            }
        }

        while (j-i < K && j < N) {
            if (cnt[c[j]] == 0) {
                ++tot;
            }
            ++cnt[c[j]];
            ++j;
        }

        ans = max(ans, tot);
    }

    cout << ans << endl;

    return 0;
}