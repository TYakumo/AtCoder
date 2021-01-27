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
    long long X;

    cin >> N >> X;
    X *= 100;

    int ans = -1;
    long long tot = 0;
    for (int i = 0; i < N; ++i) {
        long long P;
        long long V;

        cin >> P >> V;
        tot += P*V;

        if (tot > X) {
            ans = i+1;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}