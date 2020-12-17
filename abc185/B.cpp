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
    int M;
    int T;
    int cap;
    cin >> N >> M >> T;
    cap = N;

    VI A(M);
    VI B(M);

    for (int i = 0; i < M; ++i) {
        cin >> A[i] >> B[i];
    }

    int t = 0;
    for (int i = 0; i < M; ++i) {
        N -= (A[i]-t);

        if (N <= 0) {
            break;
        }

        N += B[i] - A[i];
        N = min(N, cap);
        t = B[i];
    }

    N -= (T-t);

    cout << (N <= 0 ? "No" : "Yes");


    return 0;
}