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
    long long N;

    cin >> N;

    long long now = 1;
    unordered_map <long long, int> valSet;

    int cnt = 0;
    while (now <= N/5) {
        now *= 5;
        valSet[now] = ++cnt;
    }

    bool ok = false;
    cnt = 0;
    now = 1;

    while (now <= N/3) {
        now *= 3;
        ++cnt;

        long long remain = N - now;

        if (valSet.find(remain) != valSet.end()) {
            cout << cnt << " " << valSet[remain] << endl;
            ok = true;
            break;
        }
    }

    if (!ok) {
        cout << -1 << endl;
    }

    return 0;
}