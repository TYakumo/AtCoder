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
    int X;
    int N;
    cin >> X >> N;

    unordered_set <int> valSet;

    for (int i = 0; i < N; ++i) {
        int p;
        cin >> p;
        valSet.insert(p);
    }

    int bestVal = -1000000;

    for (int v = X-2*N; v <= X+2*N; ++v) {
        if (valSet.count(v) != 0) {
            continue;
        }

        int diff = abs(v-X);

        if (diff < abs(bestVal-X)) {
            bestVal = v;
        }
    }

    cout << bestVal << endl;

    return 0;
}