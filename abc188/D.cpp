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

using VLL = vector <long long>;

int main() {
    int N;
    long long C;
    cin >> N >> C;

    map <int, long long> daySum;
    for (int i = 0; i < N; ++i) {
        int a;
        int b;
        long long c;
        cin >> a >> b >> c;
        daySum[a] += c;
        daySum[b+1] -= c;
    }

    long long nowTot = 0;
    long long ans = 0;
    auto iter = daySum.begin();
    long long preDay = -1;

    while (iter != daySum.end()) {
        if (preDay != -1) {
            ans += (iter->first-1-preDay) * min(nowTot, C);
        }
        nowTot += iter->second;
        preDay = iter->first;
        ans += min(nowTot, C);
        ++iter;
    }

    cout << ans << endl;

    return 0;
}