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
using DC = deque<char>;


int main() {
    string S;
    cin >> S;

    DC ans;
    int dir = 0;

    for (int i = 0; i < S.size(); ++i) {
        if (S[i] == 'R') {
            dir ^= 1;
        } else {
            if (dir == 0) {
                ans.push_back(S[i]);
            } else {
                ans.push_front(S[i]);
            }
        }
    }

    if (dir) {
        reverse(ans.begin(), ans.end());
    }

    DC res;
    for (int i = 0; i < ans.size(); ++i) {
        res.push_back(ans[i]);

        if (res.size() >= 2) {
            if (res.back() == res[res.size()-2]) {
                res.pop_back();
                res.pop_back();
            }
        }
    }

    for (int i = 0; i < res.size(); ++i) {
        cout << res[i];
    }
    cout << endl;

    return 0;
}