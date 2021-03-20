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
    long long mul = 10;

    for (long long v = 1; v <= 1000000; ++v) {
        if (v >= mul) {
            mul *= 10;
        }

        long long val = v*mul + v;

        if (val > N) {
            break;
        } else {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}