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
#include <queue>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;

long long solve(VI& coor, VVI& diff) {
    long long ret = 0;

    sort(coor.begin(), coor.end());

    priority_queue <int, vector<int>, greater<int>> pq; // min queue

    for (int i = 0; i < coor.size(); ++i) {
        if (i && coor[i] == coor[i-1]) {
            continue;
        }

        int p = coor[i];

        for (int j = 0; j < diff[p].size(); ++j) {
            pq.push(diff[p][j]);
        }

        // popping the min
        int setSize = p;
        while (pq.size() > setSize) {
            pq.pop();
        }
    }

    while (!pq.empty()) {
        if (pq.top() >= 0) { // negative won't be chosen, min(L[i], R[i]) is the lower bound
            ret += pq.top();
        }
        pq.pop();
    }

    return ret;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector <int> L(N);
        vector <int> R(N);
        vector <int> K(N);
        VVI coor(2);
        VVVI diff(2, VVI(N+1));

        long long ans = 0;

        for (int i = 0; i < N; ++i) {
            cin >> K[i] >> L[i] >> R[i];
            ans += min(L[i], R[i]);

            coor[0].push_back(K[i]);
            diff[0][coor[0].back()].push_back(L[i] - R[i]);

            coor[1].push_back(N-K[i]);
            diff[1][coor[1].back()].push_back(R[i] - L[i]);
        }

        for (int i = 0; i < 2; ++i) {
            ans += solve(coor[i], diff[i]);
        }

        cout << ans << endl;
    }

    return 0;
}