#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int H;
    int W;
    int K;

    cin >> H >> W >> K;

    vector <string> choco(H);

    const int INF = 100000000;
    int ans = INF;

    for (int i = 0; i < H; ++i) {
        cin >> choco[i];
    }

    int upper = 1<<(H-1);

    for (int s = 0; s < upper; ++s) {
        vector<vector <int>> groups(1);

        for (int i = 0; i < H; ++i) {
            groups.back().push_back(i);

            if ((1<<i) & s) {
                groups.push_back(vector<int>());
            }
        }

        vector <int> cnt(groups.size());
        int cut = __builtin_popcount(s);

        for (int i = 0; i < W && cut < INF; ++i) {
            bool failed = false;

            for (int j = 0; j < groups.size() && !failed; ++j) {
                for (int k = 0; k < groups[j].size(); ++k) {
                    cnt[j] += (choco[groups[j][k]][i] == '1');

                    if (cnt[j] > K) {
                        failed = true;
                        break;
                    }
                }
            }

            if (failed) {
                fill(cnt.begin(), cnt.end(), 0);
                failed = false;

                for (int j = 0; j < groups.size(); ++j) {
                    for (int k = 0; k < groups[j].size(); ++k) {
                        cnt[j] += (choco[groups[j][k]][i] == '1');

                        if (cnt[j] > K) {
                            failed = true;
                            break;
                        }
                    }
                }

                ++cut;

                if (failed) { // impossible
                    cut = INF;
                    break;
                }
            }
        }

        ans = min(ans, cut);
    }

    cout << ans << endl;

    return 0;
}