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

int main() {
    int N;

    cin >> N;
    VI A(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int ans = 1;
    int best = 0;

    for (int d = 2; d <= 1000; ++d) {
        int res = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i] % d == 0) {
                ++res;
            }
        }

        if (res > best) {
            best = res;
            ans = d;
        }
    }

    cout << ans << endl;

    return 0;
}