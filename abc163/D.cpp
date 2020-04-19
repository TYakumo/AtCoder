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
    const int MOD = 1000000000 + 7;

    int N;
    int K;
    cin >> N >> K;

    vector <long long> comb(N+2);
    vector <long long> theMin(N+2);
    vector <long long> theMax(N+2);

    comb[1] = N+1;
    theMin[1] = 0;
    theMax[1] = N;
    long long sum = N+1;

    for (int i = 2; i <= N+1; ++i) {
        theMin[i] = theMin[i-1] + (i-1);
        theMax[i] = theMax[i-1] + (N-i+1);
        comb[i] += theMax[i] - theMin[i] + 1;
        comb[i] %= MOD;

        sum += comb[i];
        sum %= MOD;
    }

    for (int i = 1; i < K; ++i) {
        sum -= comb[i];
        sum %= MOD;
    }

    sum += MOD;
    sum %= MOD;

    cout << sum << endl;

    return 0;
}