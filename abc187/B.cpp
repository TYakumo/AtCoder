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

    VI X(N);
    VI Y(N);

    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    int ans = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            int dy = Y[j]-Y[i];
            int dx = X[j] - X[i];

            if (dx != 0) {
                dy = abs(dy);
                dx = abs(dx);

                if (dy <= dx) {
                    ++ans;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}