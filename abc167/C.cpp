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
    int M;
    int X;

    cin >> N >> M >> X;
    vector <int> c(N);
    vector< vector <int> > power(N, vector<int>(M));

    for (int i = 0; i < N; ++i) {
        cin >> c[i];
        for (int j = 0; j < M; ++j) {
            cin >> power[i][j];
        }
    }

    int allTry = 1<<N;
    const int INF = 1000000000;
    int ans = INF;

    for (int s = 1; s < allTry; ++s) {
        vector <int> level(M);
        int cost = 0;

        for (int i = 0; i < N; ++i) {
            if (s & (1<<i)) {
                cost += c[i];
                for (int j = 0; j < M; ++j) {
                    level[j] += power[i][j];
                }
            }
        }

        bool pass = true;

        for (int i = 0; i < M; ++i) {
            if (level[i] < X) {
                pass = false;
                break;
            }
        }

        if (pass) {
            ans = min(ans, cost);
        }
    }

    cout << (ans == INF ? -1 : ans) << endl;


    return 0;
}