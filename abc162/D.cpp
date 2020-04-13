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

inline int chToInt(char ch) {
    if (ch == 'R') {
        return 0;
    } else if (ch == 'G') {
        return 1;
    }
    return 2;
}

int main() {
    int N;
    string str;

    cin >> N;
    cin >> str;
    long long ans = 0;

    vector< vector <int> > preSum(N+1, vector<int>(3));

    for (int i = 0; i < N; ++i) {
        preSum[i+1] = preSum[i];
        ++preSum[i+1][chToInt(str[i])];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            int num[3] = {chToInt(str[i]), chToInt(str[j])};

            if (num[0] != num[1]) {
                for (int k = 0; k < 3; ++k) {
                    if (k != num[0] && k != num[1]) {
                        num[2] = k;
                        break;
                    }
                }

                ans += (preSum[N][num[2]] - preSum[j][num[2]]);

                int diff = j-i;

                if (diff+j < N && chToInt(str[diff+j]) == num[2]) {
                    --ans;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}