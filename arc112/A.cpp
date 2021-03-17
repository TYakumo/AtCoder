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
    int T;
    cin >> T;

    for (int tc = 0; tc < T; ++tc) {
        long long L;
        long long R;
        cin >> L >> R;

        // A = B+C
        // for (long long A = R; A >= 2*L; --A) {
        //     // B = L ... A-L, (A-2*L+1);
        //     ans += (A-2*L+1);
        // }

        if (R >= 2*L) {
            long long ans = (R-2*L+1) * (R+2*L) / 2 + (R-2*L+1);
            // sum 2L ... R => (R-2L+1) * (R+2L)/2
            ans -= 2*L * (R-2*L+1);

            cout << ans << endl;
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}