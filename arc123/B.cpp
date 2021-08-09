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


int main() {
    int N;
    cin >> N;

    VVLL A(3, VLL(N));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
        sort(A[i].begin(), A[i].end());
    }

    VI idx(3);
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        while (idx[1] < N) {
            if (A[0][i] < A[1][idx[1]]) {
                while (idx[2] < N) {
                    if (A[1][idx[1]] < A[2][idx[2]]) {
                        ++ans;
                        ++idx[2];
                        break;
                    }
                    ++idx[2];
                }
                ++idx[1];
                break;
            }
            ++idx[1];
        }
    }

    cout << ans << endl;

    return 0;
}