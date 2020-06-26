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

const int INVALID_VAL = -1;

inline int getMaxValFromMap(map<int, int>& m) {
    if (m.size() == 0) {
        return INVALID_VAL;
    }

    auto iter = m.end();
    --iter;
    return iter->first;
}

inline void ifNullAndRemove(map<int, int>& m, int k) {
    auto iter = m.find(k);

    if (iter == m.end()) {
        return ;
    }

    if (iter->second == 0) {
        m.erase(iter);
    }
}

inline void moveChild(int c, int k, vector <int>& R, vector <int>& NK, vector < map<int, int> >& K,  map <int, int>& ratingVal) {
    int OK = NK[c];

    int OKMAX = getMaxValFromMap(K[OK]);
    --ratingVal[OKMAX];

    --K[OK][R[c]];
    ifNullAndRemove(K[OK], R[c]);
    int NEWOKMAX = getMaxValFromMap(K[OK]);

    if (NEWOKMAX >= 0) { // not null
        ++ratingVal[NEWOKMAX];
    }

    ifNullAndRemove(ratingVal, OKMAX);

    // transferred
    int DKMAX = getMaxValFromMap(K[k]);
    if (DKMAX >= 0) { // not null
        --ratingVal[DKMAX];
    }
    ++K[k][R[c]];

    int NEWDKMAX = getMaxValFromMap(K[k]);
    ++ratingVal[NEWDKMAX];

    ifNullAndRemove(ratingVal, DKMAX);
    NK[c] = k;
}

int main() {
    int N;
    int Q;
    cin >> N >> Q;

    const int MAXV = 200010;
    vector <int> R(N);
    vector <int> NK(N);
    vector < map<int, int> > K(MAXV);
    unordered_set <int> kSet;
    map <int, int> ratingVal;

    for (int i = 0; i < N; ++i) {
        cin >> R[i] >> NK[i];
        ++K[--NK[i]][R[i]];
        kSet.insert(NK[i]);
    }

    auto sIter = kSet.begin();
    while (sIter != kSet.end()) {
        ++ratingVal[getMaxValFromMap(K[*sIter])];
        ++sIter;
    }


    for (int i = 0; i < Q; ++i) {
        int C;
        int D;
        cin >> C >> D;
        moveChild(C-1, D-1, R, NK, K, ratingVal);

        // auto diter = ratingVal.begin();
        // cout << "Q " << i << endl;

        // while (diter != ratingVal.end()) {
        //     cout << "DEBUG " << diter->first << endl;
        //     ++diter;
        // }

        auto iter = ratingVal.begin();
        cout << iter->first << endl;
    }

    return 0;
}