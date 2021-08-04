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
using VVVLL = vector <VVLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

using VS = vector <string>;

class UnionAndFind {
    public:
    vector <int> groupSize;
    vector <int> groupParent;

    UnionAndFind (int gSize) {
        groupSize = vector<int> (gSize, 1);
        groupParent = vector<int> (gSize, -1);
    }

    int findGroup(int n) {
        if (groupParent[n] == -1) {
            return n;
        }
        return groupParent[n] = findGroup(groupParent[n]);
    }

    void unionGroup(int x, int y) {
        y = findGroup(y);
        x = findGroup(x);

        if (x == y) {
            return ;
        }

        if (groupSize[x] > groupSize[y]) {
            swap(x, y);
        }

        groupSize[y] += groupSize[x];
        groupParent[x] = y;
    }
};

void updateUT(UnionAndFind& ut, int r, int N, int curRow, int preRow) {
    int intersection = curRow & preRow;
    for (int c = 0; c < N; ++c) {
        if ((1<<c) & intersection) {
            int num1 = r*N+c;
            int num2 = (r+1)*N+c;
            ut.unionGroup(num1, num2);
        }
    }

    for (int c = 1; c < N; ++c) {
        if (((1<<c) & curRow)
        && ((1<<(c-1)) & curRow)) {
            int num1 = r*N+(c-1);
            int num2 = r*N+c;
            ut.unionGroup(num1, num2);
        }
    }
}

bool checkPrerow(UnionAndFind& ut, int r, int N, int curRow, int preRow) {
    UMI ok;
    for (int c = 0; c < N; ++c) {
        if ((1<<c) & curRow) {
            int num = r*N+c;
            int gn = ut.findGroup(num);
            ok[gn] = 1;
        }
    }

    for (int c = 0; c < N; ++c) {
        if ((1<<c) & preRow) {
            int num = (r+1)*N+c;
            int gn = ut.findGroup(num);
            if (ok.find(gn) == ok.end()) {
                return false;
            }
        }
    }

    return true;
}

void fillIn(int n, int k, int preRow, UnionAndFind ut, const VI& SC, long long& ans) {
    int N = (int)SC.size();
    if (k == 0) {
        int group = -1;
        for (int c = 0; c < N; ++c) {
            if ((1<<c) & preRow) {
                int gn = ut.findGroup(n*N + c);
                if (group == -1) {
                    group = gn;
                } else if (group != gn) {
                    return ;
                }
            }
        }

        ++ans;
        return ;
    }

    if (n == 0) {
        return ;
    }

    int UPPER = 1<<N;

    for (int cho = 0; cho < UPPER; ++cho) {
        if (cho == 0) {
            if (preRow == 0) {
                fillIn(n-1, k, cho, ut, SC, ans);
            }
            continue;
        }

        int bcnt = __builtin_popcount(cho);
        if ((cho & SC[n-1]) == 0 && bcnt <= k) {
            UnionAndFind newut = ut;
            updateUT(newut, n-1, N, cho, preRow);
            if (checkPrerow(newut, n-1, N, cho, preRow)) {
                fillIn(n-1, k-bcnt, cho, newut, SC, ans);
            }
        }
    }
}

int main() {
    int N;
    int K;
    int cnt = 0;
    cin >> N >> K;

    VS S(N);
    VI SC(N);
    UnionAndFind ut(N*N);

    for (int i = 0; i < N; ++i) {
        cin >> S[i];
        int val = 0;

        for (int j = 0; j < N; ++j) {
            if (S[i][j] == '#') {
                val |= 1<<j;
            }
        }

        SC[i] = val;
    }

    long long ans = 0;
    fillIn(N, K, 0, ut, SC, ans);
    cout << ans << endl;

    return 0;
}