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
using VVLL = vector <VLL>;

int main() {

    int L;
    cin >> L;

    VVLL comb(12, VLL(L+1));

    comb[0][0] = 1;

    for (int c = 1; c <= 11; ++c) {
        for (int j = 1; j <= L; ++j) {
            for (int i = 0; i < j; ++i) {
                comb[c][j] += comb[c-1][i];
            }
        }
    }

    long long sum = 0;
    for (int i = 11; i < L; ++i) {
        sum += comb[11][i];
    }

    cout << sum << endl;

    return 0;
}