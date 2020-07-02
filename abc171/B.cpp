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
    int K;
    cin >> N >> K;

    vector <int> p(N);

    int ans = 0;

    for (int i = 0; i < N; ++i) {
        cin >> p[i];
    }

    sort(p.begin(), p.end());

    for (int i = 0; i < K; ++i) {
        ans += p[i];
    }

    cout << ans << endl;

    return 0;
}