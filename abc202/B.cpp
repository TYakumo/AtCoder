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
    string S;
    cin >> S;

    for (int i = 0; i < S.size(); ++i) {
        if (S[i] == '6') {
            S[i] = '9';
        } else if (S[i] == '9') {
            S[i] = '6';
        }
    }

    reverse(S.begin(), S.end());
    cout << S << endl;

    return 0;
}