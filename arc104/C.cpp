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

using PI = pair<int, int>;
using VPI = vector <PI>;
using VI = vector <int>;
using VVI = vector <VI>;

int main() {
    int N;
    int ALL;
    cin >> N;

    VPI T(N);
    bool failed = false;
    ALL = 2*N;
    VI idx(ALL+1);

    for (int i = 0; i < N; ++i) {
        cin >> T[i].first >> T[i].second;
        if (T[i].second != -1 && T[i].second <= T[i].first) {
            failed = true;
        }

        if (T[i].first != -1) {
            if (idx[T[i].first] != 0) {
                failed = true;
            }
            idx[T[i].first] = i+1;
        }

        if (T[i].second != -1) {
            if (idx[T[i].second] != 0) {
                failed = true;
            }
            idx[T[i].second] = i+1;
        }
    }

    if (failed) {
        cout << "No" << endl;
    } else {
        // N^3
        VI dp(ALL+1);
        dp[0] = 1;

        for (int p = 0; p < ALL; ++p) {
            if (dp[p] == 0) {
                continue;
            }

            int start = p+1;

            for (int endP = start+1; endP <= ALL && 2*endP-1-start <= ALL; ++endP) {
                // start ... endP-1
                int newEnd = 2*endP-1-start;
                int ok = 1;
                for (int i = start; i < endP; ++i) {
                    int j = endP + (i-start); // max (endP-1-start) + endP = 2*endP-1-start

                    // fixed
                    if (idx[i] != 0 && idx[j] != 0 && idx[i] != idx[j]) {
                        ok = 0;
                        break;
                    }

                    // if start specified && end unspecified
                    if (idx[i] != 0 && idx[j] == 0) {
                        int cho = idx[i]-1;
                        if (T[cho].second != -1) {
                            ok = 0;
                            break;
                        }
                    }

                    // if start unspecified && end specified
                    if (idx[i] == 0 && idx[j] != 0) {
                        int cho = idx[j]-1;
                        if (T[cho].first != -1) {
                            ok = 0;
                            break;
                        }
                    }
                }

                dp[newEnd] |= ok;
            }
        }
        cout << (dp[ALL] != 0 ? "Yes" : "No") << endl;
    }

    return 0;
}
