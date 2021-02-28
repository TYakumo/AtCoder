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
using VVI = vector <VI>;

int main() {
    int N;
    cin >> N;

    VVI A(N, VI(3));

    int best = -1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> A[i][j];
        }

        if (A[i][2] > A[i][0]) {
            if (best == -1 || best > A[i][1]) {
                best = A[i][1];
            }
        }
    }

    cout << best << endl;

    return 0;
}