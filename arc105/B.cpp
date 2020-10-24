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
    cin >> N;

    long long ans = 0;
    set <long long> valSet;

    for (int i = 0; i < N; ++i) {
        long long val;
        cin >> val;
        valSet.insert(val);
    }

    long long sum = 0;

    while (valSet.size() >= 2) {
        long long minVal = (*valSet.begin() + sum);
        long long setVal = *valSet.begin();

        // cout << "DEBUG " << minVal << " " << setVal << endl;

        valSet.erase(valSet.begin());
        long long mul = 1;

        if (valSet.size() > 0 && minVal > 0) {
            mul = (*valSet.begin() + sum - 1) / minVal;
        }

        sum -= minVal*mul;
        valSet.insert(setVal+minVal*mul);
    }

    ans = (*valSet.begin() + sum);

    cout << ans << endl;

    return 0;
}