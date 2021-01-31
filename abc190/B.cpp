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
    long long S;
    long long D;

    cin >> N >> S >> D;

    VI X(N);
    VI Y(N);
    bool ok = false;
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];

        if (X[i] < S && Y[i] > D) {
            ok = true;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}