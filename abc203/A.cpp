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
    VI V(3);
    for (int i = 0; i < 3; ++i) {
        cin >> V[i];
    }

    sort(V.begin(), V.end());

    if (V[0] == V[1]) {
        cout << V[2] << endl;
    } else if (V[1] == V[2]) {
        cout << V[0] << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}