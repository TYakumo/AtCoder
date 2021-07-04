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
    int P;
    cin >> P;

    int ans = 0;
    VI val;

    val.push_back(1);
    int mul = 2;

    while (val.back() * mul <= P) {
        val.push_back(val.back()*mul);
        ++mul;
    }

    for (int i = (int)val.size()-1; i >= 0; --i) {
        ans += P / val[i];
        P %= val[i];
    }

    cout << ans << endl;

    return 0;
}