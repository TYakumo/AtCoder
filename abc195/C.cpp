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

    long long ans = 0;
    long long multi = 1000;
    int comma = 1;
    // 1,000 to 999,999
    // 1,000,000 to 999,999,999
    while (multi*1000-1 <= N) {
        long long nextStart = multi*1000;
        ans += (nextStart - multi) * comma;

        // next range
        multi *= 1000;
        ++comma;
    }

    if (N >= multi) {
        ans += (N-multi+1)*comma;
    }

    cout << ans << endl;

    return 0;
}