#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    long long R;
    long long X;
    long long Y;

    cin >> R >> X >> Y;

    long long dist = X*X + Y*Y;
    long long R2 = R*R;

    // ceil(sqrt(dist) / R)
    long long mul = dist/R2;
    long long num = sqrt(mul);

    while (num*num*R2 < dist) {
        ++num;
    }

    if (num <= 1 && dist != R2) {
        ++num;
    }

    cout << num << endl;

    return 0;
}