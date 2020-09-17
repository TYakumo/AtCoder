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
    long long A;
    long long B;
    long long C;
    long long D;

    cin >> A >> B >> C >> D;

    cout << max(max(B*C, A*D), max(A*C, B*D)) << endl;

    return 0;
}