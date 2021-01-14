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

int solve(const VI& rating, int N, int offset, int &loser) {
    if (N==0) {
        return offset;
    }

    int l = solve(rating, N-1, offset, loser);
    int r = solve(rating, N-1, offset+(1<<(N-1)), loser);
    int ret = l;

    if (rating[l] > rating[r]) {
        loser = r;
    } else {
        loser = l;
        ret = r;
    }

    return ret;
}

int main() {
    int N;
    cin >> N;

    int tot = 1<<N;
    VI rating(tot);
    int loser;

    for (int i = 0; i < tot; ++i) {
        cin >> rating[i];
    }

    solve(rating, N, 0, loser);
    cout << loser+1 << endl;
    return 0;
}