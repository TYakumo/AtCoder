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

int calc(int n, vector <int>& ans) {
    if (ans[n] >= 0) {
        return ans[n];
    }

    int pc = __builtin_popcount(n);
    ans[n] = calc(n%pc, ans) + 1;
    return ans[n];
}

int main() {
    int N;
    string X;

    cin >> N >> X;

    vector <int> ans(N+2, -1);
    ans[0] = 0;

    for (int i = N+1; i >= 1; --i) {
        calc(i, ans);
    }


    vector <int> pc(2);
    for (int i = 0; i < N; ++i) {
        pc[0] += (X[i] == '1');
    }

    pc[1] = pc[0]+1;
    --pc[0];

    vector <long long> res(2);

    for (int i = 0; i < N; ++i) {
        if (pc[0] > 0) {
            res[0] = (res[0]*2 + (X[i]-'0')) % pc[0];
        }

        res[1] = (res[1]*2 + (X[i]-'0')) % pc[1];
    }

    vector <long long> mul(2, 1);
    vector <int> finalRes(N);

    for (int i = N-1; i >= 0; --i) {
        if (X[i] == '0') { // to be pc[1]
            long long newres = (res[1] + mul[1]) % pc[1];
            finalRes[i] = calc(newres, ans) + 1;
        } else { // pc[0]
            if (pc[0] == 0) {
                finalRes[i] = 0;
            } else {
                long long newres = ((res[0] - mul[0])%pc[0] + pc[0]) % pc[0];
                finalRes[i] = calc(newres, ans) + 1;
            }
        }

        if (pc[0] > 0) {
            mul[0] = mul[0]*2%pc[0];
        }

        mul[1] = mul[1]*2%pc[1];
    }

    for (int i = 0; i < finalRes.size(); ++i) {
        cout << finalRes[i] << endl;
    }

    return 0;
}