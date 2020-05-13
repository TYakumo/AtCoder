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
#include <cstring>
#include <queue>
using namespace std;

const int MAXS = 1000010;
char str[MAXS];

int main() {
    int N;
    unordered_map <int, deque<int>> posCho;
    unordered_map <int, deque<int>> negCho;

    cin >> N;
    int maxRight = 0;
    int maxLeft = 0;

    const int INF = 100000000;
    int minLcnt = INF;
    int minRcnt = INF;

    for (int i = 0; i < N; ++i) {
        scanf("%s", str);
        int len = strlen(str);
        vector <char> stk;

        for (int j = 0; j < len; ++j) {
            if (str[j] == '(') {
                stk.push_back('(');
            } else {
                if (!stk.empty() && stk.back() == '(') {
                    stk.pop_back();
                } else {
                    stk.push_back(')');
                }
            }
        }

        int j = 0;
        int lcnt = 0;
        int rcnt = 0;
        while (j < stk.size()) {
            if (stk[j] == ')') {
                ++rcnt;
                ++j;
            } else {
                break;
            }
        }

        lcnt = stk.size() - j;
        maxRight = max(maxRight, rcnt);
        maxLeft = max(maxLeft, lcnt);

        if (lcnt >= rcnt) {
            posCho[rcnt].push_back(lcnt);
        } else {
            negCho[lcnt].push_back(rcnt);
        }

        minLcnt = min(minLcnt, lcnt);
        minRcnt = min(minRcnt, rcnt);
    }

    bool failed = false;
    int totLcnt = 0;
    int totRcnt = 0;

    for (int v = 0; v <= maxRight && !failed; ++v) {
        for (int j = 0; j < posCho[v].size(); ++j) {
            if (totLcnt < v) {
                failed = true;
                break;
            } else {
                totLcnt += (posCho[v][j] - v);
            }
        }
    }

    for (int v = 0; v <= maxLeft && !failed; ++v) {
        for (int j = 0; j < negCho[v].size(); ++j) {
            if (totRcnt < v) {
                failed = true;
                break;
            } else {
                totRcnt += (negCho[v][j] - v);
            }
        }
    }

    cout << (failed || totLcnt != totRcnt || minLcnt > 0 || minRcnt > 0 ? "No" : "Yes") << endl;

    return 0;
}