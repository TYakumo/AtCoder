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
    long long N;
    long long K;

    cin >> N >> K;

    long long V = N / K;

    N -= V*K;
    long long theMin = N;

    // N < K
    // |N-K| = K-N
    // K-N - K = N
    for (int i = 0; i < 2; ++i) {
        N -= K;

        if (N < 0) {
            N = -N;
        }

        theMin = min(theMin, N);
    }


    cout << theMin << endl;


    return 0;
}