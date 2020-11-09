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

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

void normalized(int& dx, int& dy) {
    int g = gcd(dx, dy);
    dx /= g;
    dy /= g;

    if (dx < 0) {
        dx = -dx;
        dy = -dy;
    }

    if (dx == 0) {
        dy = abs(dy);
    }
}

int main() {
    int N;

    cin >> N;

    VI x(N);
    VI y(N);
    map <VI, set<pair<int, int>>> pnts;

    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            int dx = x[i] - x[j];
            int dy = y[i] - y[j];

            normalized(dx, dy);
            // (x, y) = d(dx, dy) + (x', y')
            // ax+by = c
            int c = dy * x[i] - dx * y[i];
            VI param = {dx, dy, c};

            pnts[param].insert(make_pair(x[i], y[i]));
            pnts[param].insert(make_pair(x[j], y[j]));
        }
    }

    bool found = false;

    auto iter = pnts.begin();

    while (iter != pnts.end()) {
        if (iter->second.size() >= 3) {
            found = true;
            break;
        }
        ++iter;
    }

    cout << (found ? "Yes" : "No") << endl;
    return 0;
}