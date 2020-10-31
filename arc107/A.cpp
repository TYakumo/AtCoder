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
    const long long MOD = 998244353;
    long long A;
    long long B;
    long long C;

    cin >> A >> B >> C;

    C = C*(C+1)/2%MOD;
    B = B*(B+1)/2%MOD;
    A = A*(A+1)/2%MOD;

    cout << A*B%MOD*C%MOD << endl;

    return 0;
}