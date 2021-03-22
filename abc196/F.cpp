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

using Modint = modint998244353;
using VI = vector <Modint>;


int main() {
    string S;
    string T;

    cin >> S;
    cin >> T;
    reverse(T.begin(), T.end());

    VI SV(S.size());
    VI TV(S.size());
    VI ISV(S.size());
    VI ITV(S.size());

    for (int i = 0; i < S.size(); ++i) {
        int val = S[i]-'0';
        SV[i] = val;
        ISV[i] = val^1;
    }

    for (int i = 0; i < T.size(); ++i) {
        int val = T[i]-'0';
        TV[i] = val;
        ITV[i] = val^1;
    }

    int ans = T.size();
    VI f1 = convolution(SV, ITV);
    VI f2 = convolution(ISV, TV);

    for (int i = T.size()-1; i < S.size(); ++i) {
        int cost = f1[i].val() + f2[i].val();
        ans = min(ans, cost);
    }

    cout << ans << endl;

    return 0;
}