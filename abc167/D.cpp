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

int main() {
    int N;
    long long K;
    cin >> N >> K;

    vector <int> tele(N);

    for (int i = 0; i < N; ++i) {
        cin >> tele[i];
        --tele[i];
    }

    int count = 0;
    int cycle = 0;
    int offset = 0;
    vector<int> used(N, -1);
    vector<int> vertex(N);

    deque <int> que;
    que.push_back(0);

    while (!que.empty()) {
        int now = que.front();
        que.pop_front();

        if (used[now] >= 0) {
            cycle = count-used[now];
            offset = used[now];
            break;
        }

        used[now] = count;
        vertex[count++] = now;

        que.push_back(tele[now]);
    }

    if (K <= offset) {
        cout << (vertex[K]+1) << endl;
    } else {
        K -= offset;
        K %= cycle;
        cout << (vertex[K+offset]+1) << endl;
    }

    return 0;
}