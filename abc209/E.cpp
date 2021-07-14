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
using SI = set<int>;
using VSI = vector<SI>;
using UMLL = unordered_map<long long, long long>;

using VS = vector <string>;
const int UPPER = 52*52*52;

enum class GameType {
    NONDEF,
    DRAW,
    WIN,
    LOSE
};

using VG = vector<GameType>;

inline int charToInt(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch-'a'+26;
    }
    return ch-'A';
}

int suffixToInt(const string& s) {
    int ret = 0;
    for (int i = 0; i < 3; ++i) {
        int offset = (int)s.size()-3;
        ret = ret*52 + charToInt(s[offset+i]);
    }
    return ret;
}

int prefixToInt(const string& s) {
    int ret = 0;
    for (int i = 0; i < 3; ++i) {
        ret = ret*52 + charToInt(s[i]);
    }
    return ret;
}

int main() {
    int N;
    cin >> N;

    VS words(N);
    VI sufSt(N);
    VI preSt(N);

    VI appear(UPPER);
    VI winCnt(UPPER);
    VI oneLose(UPPER);
    VI used(UPPER);
    VVI preList(UPPER);
    VVI sufList(UPPER);

    for (int i = 0; i < N; ++i) {
        cin >> words[i];
        preSt[i] = prefixToInt(words[i]);
        sufSt[i] = suffixToInt(words[i]);
        appear[preSt[i]] = 1;
        preList[preSt[i]].push_back(i);
        sufList[sufSt[i]].push_back(i);
    }

    deque <int> que;
    for (int i = 0; i < UPPER; ++i) {
        if (appear[i]) {
            for (int j = 0; j < preList[i].size(); ++j) {
                int idx = preList[i][j];

                if (appear[sufSt[idx]] == 0) {
                    oneLose[i] = 1;

                    if (!used[i]) {
                        used[i] = 1;
                        que.push_back(i);
                    }
                }
            }
        }
    }

    while (!que.empty()) {
        int st = que.front();
        que.pop_front();

        if (winCnt[st] == preList[st].size()) {
            for (int j = 0; j < sufList[st].size(); ++j) {
                int idx = sufList[st][j];
                int preState = preSt[idx];
                oneLose[preState] = 1;

                if (used[preState] == 0) {
                    used[preState] = 1;
                    que.push_back(preState);
                }
            }
        } else if (oneLose[st]) {
            for (int j = 0; j < sufList[st].size(); ++j) {
                int idx = sufList[st][j];
                int preState = preSt[idx];
                ++winCnt[preState];

                if (winCnt[preState] == preList[preState].size() && used[preState] == 0) {
                    used[preState] = 1;
                    que.push_back(preState);
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        GameType res = GameType::NONDEF;

        if (appear[sufSt[i]]) {
            if (oneLose[sufSt[i]]) {
                res = GameType::WIN;
            } else if (winCnt[sufSt[i]] == preList[sufSt[i]].size()) {
                res = GameType::LOSE;
            }
        } else {
            res = GameType::LOSE;
        }

        if (res == GameType::WIN) {
            cout << "Aoki" << endl;
        } else if (res == GameType::LOSE) {
            cout << "Takahashi" << endl;
        } else {
            cout << "Draw" << endl;
        }
    }

    return 0;
}