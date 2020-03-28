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

int dist(int a, int b, int K) {
    return min(abs(a-b), K-abs(a-b));
}

int main() {
    int N;
    int K;
    cin >> K >> N;
    vector <int> loc(N);

    for (int i = 0; i < N; ++i) {
        cin >> loc[i];
    }

    int ans = K;
    sort(loc.begin(), loc.end());

    for (int i = 0; i < N; ++i) {
        ans = min(ans, K - max(dist(loc[(i+N-1)%N], loc[i], K), dist(loc[(i+1)%N], loc[i], K)));
    }

    cout << ans << endl;

    return 0;
}