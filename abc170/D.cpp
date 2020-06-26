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
    cin >> N;
    int MAXVAL = 0;


    vector <int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        MAXVAL = max(A[i], MAXVAL);
    }

    vector <bool> divided(MAXVAL+1);
    unordered_map <int, int> valSet;

    for (int i = 0; i < N; ++i) {
        if (valSet[A[i]] >= 2) {
            continue;
        }

        ++valSet[A[i]];

        if (valSet[A[i]] == 2) {
            divided[A[i]] = true;
        }

        for (int m = 2; m*A[i] <= MAXVAL; ++m) {
            divided[m*A[i]] = true;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (!divided[A[i]]) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}