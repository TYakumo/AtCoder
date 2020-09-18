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
#include <queue>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;

struct PQue {
    int cnt;
    int val;

    PQue(int pc, int pv) : cnt(pc), val(pv) {
    }

    bool operator<(const PQue& a) const {
        if (cnt != a.cnt) {
            return cnt < a.cnt;
        }
        return val < a.val;
    }
};

using PQ = priority_queue <PQue>;

void handle(PQ& outPq, PQ& inPq, VVI& cnt, int v) {
    if (cnt[1][v] > 0) {
        int sum = cnt[0][v]+cnt[1][v];
        if (cnt[0][v] == 0 || outPq.empty() || sum > outPq.top().cnt) {
            outPq.push(PQue(sum, v));
        } else if (cnt[0][v] > 0) {
            inPq.push(PQue(sum, v));
        }
    } else if (cnt[0][v] > 0) {
        inPq.push(PQue(cnt[0][v] + cnt[1][v], v));
    }
}

int main() {
    // No => if max(#Bi) >= Sigma#Aj where Aj != Bi
    int N;
    cin >> N;

    VI A[2];

    VVI cnt(2, VI(N+1));
    vector <set<int>> idxSet(N+1);
    PQ outPq;
    PQ inPq;

    for (int i = 0; i < 2; ++i) {
        A[i] = std::move(vector<int>(N));
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
            ++cnt[i][A[i][j]];
            if (i == 0) {
                idxSet[A[i][j]].insert(j);
            }
        }
    }

    // for ch, #ch in A+B <= #total A (constant)
    int theMax = -1;
    int theMaxVal = -1;

    for (int v = 1; v <= N; ++v) {
        if (cnt[1][v] > 0) {
            int sum = cnt[0][v]+cnt[1][v];
            if (sum > theMax) {
                theMax = sum;
                theMaxVal = v;
            }
        }
    }

    handle(outPq, inPq, cnt, theMaxVal);

    for (int v = 1; v <= N; ++v) {
        if (v != theMaxVal) {
            handle(outPq, inPq, cnt, v);
        }
    }

    VI ans(N);
    bool ok = true;

    while (!outPq.empty()) {
        int outCho = outPq.top().val;
        outPq.pop();

        if (inPq.empty()) {
            ok = false;
            break;
        }

        int inCho = inPq.top().val;
        inPq.pop();

        auto iter = idxSet[inCho].begin();
        ans[*iter] = outCho;
        idxSet[inCho].erase(iter);

        --cnt[0][inCho];
        --cnt[1][outCho];

        handle(outPq, inPq, cnt, outCho);
        handle(outPq, inPq, cnt, inCho);
    }

    if (ok) {
        cout << "Yes" << endl;
        cout << ans[0] ;
        for (int i = 1; i < N; ++i) {
            cout << " " << ans[i] ;
        }
        cout << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}