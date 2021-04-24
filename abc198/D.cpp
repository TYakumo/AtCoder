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
using UMCL = unordered_map<char, long long>;
using VS = vector <string>;

bool checkValid(const VS& S, UMCL& dMap, int len) {
    VLL res(3);

    for (int i = 0; i < 3; ++i) {
        int lendiff = len - ((int)S[0].size() - (int)S[i].size());

        for (int j = 0; j < lendiff; ++j) {
            res[i] = res[i]*10 + dMap[S[i][j]];
        }
    }

    return res[0] <= res[1]+res[2]+1 && res[0] >= res[1]+res[2];
}

void solve(const VS& S, UMCL dMap, VI& used, int now, int len, VLL& ans) {
    if (ans.size()) {
        return ;
    }

    int maxlen = max(S[0].size(), max(S[1].size(), S[2].size()));

    if (len == maxlen) {
        // final check
        VLL res(3);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < S[i].size(); ++j) {
                res[i] = res[i]*10LL + dMap[S[i][j]];
            }
        }

        if (res[0] == res[1] + res[2] && res[1] > 0 && res[2] > 0) {
            ans = res;
        }
        return ;
    }

    if (now == 0 && len > 0 && checkValid(S, dMap, len) == false) {
        return ;
    }

    if (len < S[now].size()) {
        char ch = S[now][len];

        if (dMap.find(ch) != dMap.end()) { // no choice
            if (now == S.size()-1) {
                solve(S, dMap, used, 0, len+1, ans);
            } else {
                solve(S, dMap, used, now+1, len, ans);
            }
        } else {
            // int start = len > 0 || (S[now].size() == 1) ? 0 : 1;
            int start = len > 0 ? 0 : 1;

            for (int d = start; d <= 9; ++d) {
                if (used[d]) {
                    continue;
                }

                used[d] = 1;
                UMCL newDMap = dMap;
                newDMap[ch] = d;

                if (now == S.size()-1) {
                    solve(S, newDMap, used, 0, len+1, ans);
                } else {
                    solve(S, newDMap, used, now+1, len, ans);
                }
                used[d] = 0;
            }
        }
    } else{
        if (now == S.size()-1) {
            solve(S, dMap, used, 0, len+1, ans);
        } else {
            solve(S, dMap, used, now+1, len, ans);
        }
    }
}

int main() {
    VS S(3);

    set <char> chSet;

    for (int i = 0; i < 3; ++i) {
        cin >> S[i];
        for (int j = 0; j < S[i].size(); ++j) {
            chSet.insert(S[i][j]);
        }
    }

    swap(S[0], S[2]);

    if (chSet.size() > 10) {
        cout << "UNSOLVABLE" << endl;
    } else {
        VI used(11);
        UMCL dMap;
        VLL ans;
        solve(S, dMap, used, 0, 0, ans);

        if (ans.size()) {
            swap(ans[0], ans[2]);
            for (int i = 0; i < 3; ++i) {
                cout << ans[i] << endl;
            }
        } else {
            cout << "UNSOLVABLE" << endl;
        }
    }



    return 0;
}