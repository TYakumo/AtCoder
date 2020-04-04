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

const int MAXS = 300010;
char str[MAXS];

int main() {
    int N;
    int K;
    int C;

    scanf("%d %d %d", &N, &K, &C);
    scanf("%s", str);

    vector <int> best(N);
    vector <int> slack(N, K);

    ++C;
    for (int i = 0; i < N; ++i) {
        if (i) {
            best[i] = max(best[i], best[i-1]);
        }

        if (str[i] == 'o') {
            int preMax = 0;

            if (i-C >= 0) {
                preMax = best[i-C];
            }


            best[i] = max(best[i], preMax+1);
        }
    }

    for (int i = N-1; i >= 0; --i) {
        if (str[i] == 'o') {
            if (i-C >= 0) {
                slack[i-C] = min(slack[i-C], slack[i]-1);
            }
        }

        if (i) {
            slack[i-1] = min(slack[i-1], slack[i]);
        }
    }

    unordered_map <int, int> critCount;

    for (int i = 0; i < N; ++i) {
        if (slack[i] == best[i] && str[i] == 'o') {
            ++critCount[best[i]];
        }
    }

    for (int i = 0; i < N; ++i) {
        if (slack[i] == best[i] && str[i] == 'o' && critCount[best[i]] == 1) {
            cout << i+1 << endl;;
        }
    }

    return 0;
}