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

int main() {
    const long long MOD = 1000000000 + 7;

    int N;
    int K;
    cin >> N >> K;

    vector <long long> posVal;
    vector <long long> negVal;
    long long res = 1;

    for (int i = 0; i < N; ++i) {
        long long val;
        cin >> val;

        if (val < 0) {
            negVal.push_back(val);
        } else {
            posVal.push_back(val);
        }
    }

    int RK = K - min(K/2*2, ((int)negVal.size()/2) * 2);

    // must be negative
    if (RK > posVal.size()) {
        int idx[2] = {0, 0};
        sort(posVal.begin(), posVal.end());
        sort(negVal.begin(), negVal.end(), greater<int>());

        while (K > 0) {
            if (idx[0] < posVal.size() && idx[1] < negVal.size()) {
                if (abs(posVal[idx[0]]) < abs(negVal[idx[1]])) {
                    res *= posVal[idx[0]++];
                    res %= MOD;
                } else {
                    res *= negVal[idx[1]++];
                    res %= MOD;
                }
            } else if (idx[0] < posVal.size()) {
                res *= posVal[idx[0]++];
                res %= MOD;
            } else {
                res *= negVal[idx[1]++];
                res %= MOD;
            }
            --K;
        }
    } else { // can be positive
        int idx[2] = {0, 0};
        sort(posVal.begin(), posVal.end(), greater<int>());
        sort(negVal.begin(), negVal.end());

        while (K >= 2 && idx[1]+2 <= negVal.size()) {
            long long mul[2] = {0, negVal[idx[1]] * negVal[idx[1]+1]};
            int plus = 0;

            if (idx[0]+2 <= posVal.size()) {
                mul[0] = posVal[idx[0]] * posVal[idx[0]+1];
                plus = 2;
            } else if (idx[0]+1 <= posVal.size()) {
                mul[0] = posVal[idx[0]];
                plus = 1;
            }

            if (mul[0] > mul[1]) {
                mul[0] %= MOD;
                res *= mul[0];
                res %= MOD;
                idx[0] += plus;
                K -= plus;
            } else {
                mul[1] %= MOD;
                res *= mul[1];
                res %= MOD;
                idx[1] += 2;
                K -= 2;
            }
        }

        while (K > 0 && idx[0] < posVal.size()) {
            res *= posVal[idx[0]++];
            res %= MOD;
            --K;
        }
    }

    cout << ((res + MOD) % MOD) << endl;

    return 0;
}