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

using VI = vector<int>;
using VLL = vector<long long>;
using VVLL = vector <VLL>;

void genComb(VI& A, int to, int now, long long sum, VLL& comb) {
    if (now == to) {
        comb.push_back(sum);
        return ;
    }

    genComb(A, to, now+1, sum+A[now], comb);
    genComb(A, to, now+1, sum, comb);
}

int main() {
    int N;
    long long T;
    cin >> N >> T;

    VI A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    if (N >= 2) {
        VVLL comb(2);
        genComb(A, N/2, 0, 0, comb[0]);
        genComb(A, N, N/2, 0, comb[1]);

        sort(comb[0].begin(), comb[0].end());
        sort(comb[1].begin(), comb[1].end());
        long long ans = 0;

        for (int i = 0; i < comb[0].size(); ++i) {
            if (i && comb[0][i] == comb[0][i-1]) {
                continue;
            }

            if (comb[0][i] <= T) {
                long long remain = T - comb[0][i];
                int low = 0;
                int up = comb[1].size()-1;

                while (low <= up) {
                    int mid = (low+up) / 2;

                    if (comb[1][mid] + comb[0][i] <= T) {
                        ans = max(ans, comb[1][mid] + comb[0][i]);
                        low = mid+1;
                    } else {
                        up = mid-1;
                    }
                }
            } else {
                break;
            }
        }

        cout << ans << endl;
    } else {
        if (A[0] <= T) {
            cout << A[0] << endl;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}