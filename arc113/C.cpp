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

using VLL = vector <long long>;

int main() {
    string s;
    cin >> s;

    long long ans = 0;
    VLL counter(26);
    ++counter[s.back()-'a'];

    for (int i = s.size()-2; i >= 0; --i) {
        if (s[i] == s[i+1]) {
            long long totChar = s.size()-i;
            ans += totChar-2;
            ans -= counter[s[i]-'a']-1;
            counter = VLL(26, 0);
            counter[s[i]-'a'] = totChar;
        } else {
            ++counter[s[i]-'a'];
        }
    }

    cout << ans << endl;

    return 0;
}