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
    long long ans = 0;
    int N;

    cin >> N;

    for (int i = 1; i <= N; ++i) {
        if (i%3 != 0 && i%5 != 0) {
            ans += i;
        }
    }

    cout << ans << endl;

    return 0;
}