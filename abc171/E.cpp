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
    int N;
    cin >> N;

    vector <long long> A(N);
    vector <long long> ans(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    for (int b = 31; b >= 0; --b) {
        long long v = 1LL << b;

        vector <int> cnt(2);
        for (int i = 0; i < N; ++i) {
            if (A[i] & v) {
                ++cnt[1];
            } else {
                ++cnt[0];
            }
        }

        vector <int> cho(2, -1);
        vector <int> flag(2);
        for (int i = 0; i < 2; ++i) {
            flag[i] = cnt[i]%2;
        }

        for (int o = 0; o < 2 && cho[1] < 0; ++o) {
            for (int e = 0; e < 2; ++e) {
                int ores = ((flag[1]^1) * o) ^ (flag[0] * e);
                int eres = ((flag[0]^1) * e) ^ (flag[1] * o);

                if (ores == 1 && eres == 0) {
                    cho[0] = e;
                    cho[1] = o;
                    break;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (A[i] & v) {
                ans[i] |= v * cho[1];
            } else {
                ans[i] |= v * cho[0];
            }
        }
    }

    string delimit;
    for (int i = 0; i < N; ++i) {
        cout << delimit << ans[i];
        delimit = " ";
    }
    cout << endl;
    return 0;
}