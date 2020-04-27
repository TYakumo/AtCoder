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
#include <cstring>
using namespace std;

const int MAXS = 300000;
char str[MAXS];

int main() {
    scanf("%s", str);

    int N = strlen(str);
    const int MOD = 2019;

    int mul = 1;
    int prefixSum = 0;
    long long ans = 0;
    unordered_map <int, int> remainMap;

    for (int i = N-1; i >= 0; --i) {
        prefixSum += (str[i]-'0') * mul;
        prefixSum %= MOD;

        if (prefixSum == 0) {
            ++ans;
        }

        // int target = prefixSum;
        ans += remainMap[prefixSum];
        ++remainMap[prefixSum];

        mul *= 10;
        mul %= MOD;
    }

    cout << ans << endl;

    return 0;
}