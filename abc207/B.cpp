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
    long long A;
    long long B;
    long long C;
    long long D;

    cin >> A >> B >> C >> D;

    // (A + B*T) / C*T <= D
    // (A + B*T) <= D*C*T
    // A <= (D*C-B)*T
    // A/(D*C-B) <= T

    long long div = (D*C-B);

    if (A != 0 && div <= 0) {
        cout << -1 << endl;
    } else if (A == 0) {
        cout << 0 << endl;
    } else {
        long long T = (A+div-1)/div;
        cout << T << endl;
    }


    return 0;
}