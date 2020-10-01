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
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    long long A;
    long long B;
    long long C;
    long long D;
    cin >> A >> B >> C >> D;

    if (A > C) {
        swap(A, C);
        swap(B, D);
    }

    // A <= C
    if (B >= C) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}