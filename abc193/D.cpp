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

using VI = vector <int>;
using VVI = vector <VI>;
using VLL = vector <long long>;

int main() {
    int K;
    cin >> K;
    string S;
    string T;

    cin >> S >> T;

    double winning = 0;
    VLL remain(10, K);
    VVI cnt(2, VI(10));

    for (int i = 0; i < 4; ++i) {
        --remain[S[i]-'0'];
        --remain[T[i]-'0'];
        ++cnt[0][S[i]-'0'];
        ++cnt[1][T[i]-'0'];
    }

    long long totCard = 9*K-8;

    for (int a = 1; a <= 9; ++a) {
        for (int b = 1; b <= 9; ++b) {
            double prob = 0;
            VVI ncnt = cnt;
            ++ncnt[0][a];
            ++ncnt[1][b];

            if (a==b) {
                if (remain[a] < 2) {
                    continue;
                }
                prob = (double)remain[a]*(remain[b]-1)/(totCard*(totCard-1));
            } else {
                if (remain[a] < 1 || remain[b] < 1) {
                    continue;
                }
                prob = (double)remain[a]*remain[b]/(totCard*(totCard-1));
            }

            VLL score(2);

            for (int i = 0; i < 2; ++i) {
                for (int j = 1; j <= 9; ++j) {
                    long long base = j;
                    for (int k = 0; k < ncnt[i][j]; ++k) {
                        base *= 10;
                    }

                    score[i] += base;
                }
            }

            // if T wins
            if (score[0] > score[1]) {
                winning += prob;
            }
        }
    }

    cout << setprecision(15) << fixed << winning << endl;

    return 0;
}