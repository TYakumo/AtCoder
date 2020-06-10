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
    long long res = 1;
    const long long UPPER = 1000000000LL * 1000000000LL;

    int N;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        long long v;
        cin >> v;

        if (v == 0) {
            res = 0;
            break;
        }

        if (res < 0) {
            continue;
        }

        if (res <= UPPER/v) {
            res *= v;
        } else {
            res = -1;
        }

        if (res > UPPER) {
            res = -1;
        }
    }

    cout << res << endl;

    return 0;
}