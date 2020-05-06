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

using VI = vector <int>;
using VVI = vector <VI>;

struct SegmentTree {
    const int INVALID_VAL = -1;
    int val;
    int from;
    int to;
    SegmentTree *left;
    SegmentTree *right;

    SegmentTree (int treeSize) {
        from = 0;
        to = 1;
        val = INVALID_VAL;

        while ((to-from) < treeSize) {
            to *= 2;
        }

        left = right = nullptr;
    }

    SegmentTree (int pf, int pt) : from(pf), to(pt) {
        val = INVALID_VAL;
        left = right = nullptr;
    }

    int updateSegment(int f, int t, int val) {
        if (f >= t) {
            return INVALID_VAL;
        }

        if (f == from && t == to) {
            this->val = val;
            return this->val;
        }

        int mid = (from + to) / 2;
        if (left == nullptr) {
            left = new SegmentTree(from, mid);
            right = new SegmentTree(mid, to);
        }

        if (t > mid) {
            right->updateSegment(max(f, mid), t, val);
        }

        if (f < mid) {
            left->updateSegment(f, min(t, mid), val);
        }

        this->val = max(left->val, right->val);
        return this->val;
    }

    int findMax(int f, int t) {
        if (f >= t) {
            return INVALID_VAL;
        }

        if (f == from && t == to) {
            return this->val;
        }

        int mid = (from + to) / 2;
        int maxVal = INVALID_VAL;

        if (left == nullptr) {
            left = new SegmentTree(from, mid);
            right = new SegmentTree(mid, to);
        }

        if (t > mid) {
            maxVal = max(maxVal, right->findMax(max(f, mid), t));
        }

        if (f < mid) {
            maxVal = max(maxVal, left->findMax(f, min(t, mid)));
        }

        return maxVal;
    }
};

void solve(int now, int parent, VVI& adja, VI& val, VI& ans, SegmentTree* st) {
    ans[now] = 1;
    int maxVal = max(0, st->findMax(0, val[now]));

    int backupVal = st->findMax(val[now], val[now]+1);
    if (backupVal < maxVal+1) {
        st->updateSegment(val[now], val[now]+1, maxVal+1);
    }

    ans[now] = max(ans[now], st->val);

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];
        if (nextv != parent) {
            solve(nextv, now, adja, val, ans, st);
        }
    }

    st->updateSegment(val[now], val[now]+1, backupVal);
}

int main() {
    int N;
    cin >> N;

    VI val(N);
    VI ans(N);
    VVI adja(N);

    for (int i = 0; i < N; ++i) {
        cin >> val[i];
    }

    // relabel val
    VI sortedVal(val.begin(), val.end());
    unordered_map <int, int> valMap;
    int V = 0;

    sort(sortedVal.begin(), sortedVal.end());

    valMap[sortedVal[0]] = V++;

    for (int i = 1; i < sortedVal.size(); ++i) {
        if (sortedVal[i] != sortedVal[i-1]) {
            valMap[sortedVal[i]] = V++;
        }
    }

    for (int i = 0; i < val.size(); ++i) {
        val[i] = valMap[val[i]];
    }

    SegmentTree* st = new SegmentTree(V);

    // tree map
    for (int i = 1; i < N; ++i) {
        int f;
        int t;
        cin >> f >> t;

        --f;
        --t;
        adja[f].push_back(t);
        adja[t].push_back(f);
    }

    solve(0, -1, adja, val, ans, st);

    for (int i = 0; i < N; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}