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
    int N;
    long long D;
    cin >> N >> D;

    D = D*D;
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        long long X;
        long long Y;
        cin >> X >> Y;

        if (X*X + Y*Y <= D) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}