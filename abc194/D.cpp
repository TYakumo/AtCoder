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

using VD = vector <double>;

int main() {
    int N;
    cin >> N;

    VD ans(N+1);

    double harmony = 0;
    for (int n = 2; n <= N; ++n) {
        harmony += 1.0/(n-1.0);
        ans[n] = n*harmony;
    }

    cout << setprecision(15) << fixed << ans[N] << endl;

    return 0;
}