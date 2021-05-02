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

    int ans = 0;
    for (int i = 0; i+3 < S.size(); ++i) {
        if (S[i] == 'Z' && S[i+1] == 'O' && S[i+2] == 'N' && S[i+3] == 'e') {
            ++ans;
        }
    }

    cout << ans << endl;


    return 0;
}