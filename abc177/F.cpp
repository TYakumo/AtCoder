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

inline void decreaseByOne(multiset<int>& mset, int val) {
    mset.erase(mset.lower_bound(val));
}

int main() {
    int H;
    int W;
    cin >> H >> W;

    const int INF = 10000000;
    map <int, int> dp;
    multiset <int> cand;

    for (int p = 1; p <= W; ++p) {
        dp[p] = 0;
        cand.insert(0);
    }

    for (int h = 0; h < H; ++h) {
        int A;
        int B;
        cin >> A >> B;

        int newVal = INF;
        // update interval [A, B]
        auto iter = dp.lower_bound(A);
        while (iter != dp.end() && iter->first <= B) {
            int dist = B+1 - iter->first + iter->second;
            newVal = min(newVal, dist);
            // erase candidates
            decreaseByOne(cand, iter->second);

            auto nextIter = iter;
            ++nextIter;
            dp.erase(iter);
            iter = nextIter;
        }

        if (newVal != INF) {
            if (B+1 <= W) {
                if (dp.count(B+1)) { // update
                    if (newVal < dp[B+1]) {
                        decreaseByOne(cand, dp[B+1]);

                        dp[B+1] = newVal;
                        cand.insert(newVal);
                    }
                } else {
                    dp[B+1] = newVal;
                    cand.insert(newVal);
                }
            }
        }

        if (cand.empty()) {
            cout << -1 << endl;
        } else {
            cout << *cand.begin() + h + 1 << endl;
        }
    }
    return 0;
}