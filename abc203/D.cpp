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
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

inline int getSum(const VVI& acc, int sr, int sc, int er, int ec) {
    if (er < sr || ec < sc) {
        return 0;
    }

    int ret = acc[er][ec];

    if (sr-1 >= 0) {
        ret -= acc[sr-1][ec];
    }

    if (sc-1 >= 0) {
        ret -= acc[er][sc-1];
    }

    if (sr-1 >= 0 && sc-1 >= 0) {
        ret += acc[sr-1][sc-1];
    }

    return ret;
}

int main() {
    int N;
    int K;
    cin >> N >> K;

    VVI val(N, VI(N));
    VI valVec;
    UMI rankMap;
    UMI rankToVal;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> val[i][j];
            valVec.push_back(val[i][j]);
        }
    }

    int cnt = 0;
    sort(valVec.begin(), valVec.end());
    rankMap[valVec[0]] = ++cnt;
    rankToVal[cnt] = valVec[0];

    for (int i = 1; i < valVec.size(); ++i) {
        if (valVec[i] != valVec[i-1]) {
            rankMap[valVec[i]] = ++cnt;
            rankToVal[cnt] = valVec[i];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            val[i][j] = rankMap[val[i][j]];
        }
    }

    int target = K%2 ? (K*K)/2+1 : (K*K)/2;
    int low = 1;
    int up = rankToVal.size();
    int ans = -1;

    while (low <= up) {
        int mid = (low+up) / 2;

        VVI mask(N, VI(N));
        VVI acc(N, VI(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                mask[i][j] = val[i][j] <= mid;
            }
        }

        for (int i = 0; i < N; ++i) {
            int racc = 0;
            for (int j = 0; j < N; ++j) {
                racc += mask[i][j];

                if (i) {
                    acc[i][j] += acc[i-1][j];
                }
                acc[i][j] += racc;
            }
        }

        bool ok = false;
        for (int i = 0; i+K-1 < N && !ok; ++i) {
            for (int j = 0; j+K-1 < N && !ok; ++j) {
                int sum = getSum(acc, i, j, i+K-1, j+K-1);
                if (sum >= target) {
                    ok = true;
                    break;
                }
            }
        }

        if (ok) {
            up = mid-1;
            ans = rankToVal[mid];
        } else {
            low = mid+1;
        }
    }

    cout << ans << endl;

    return 0;
}