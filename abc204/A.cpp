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
    int x;
    int y;
    cin >> x >> y;

    if (x != y) {
        int z = 0;
        for (int i = 0; i < 3; ++i) {
            if (i != x && i != y) {
                z = i;
                break;
            }
        }
        cout << z << endl;
    } else if (x == y) {
        cout << y << endl;
    }

    return 0;
}