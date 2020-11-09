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

int main() {
    string S;
    cin >> S;

    VI cnt(10, 0);

    for (int i = 0; i < S.size(); ++i) {
        if (S[i] >= '1' && S[i] <= '9') {
            ++cnt[S[i]-'0'];
        }
    }

    cnt[0] = 10000;
    bool ok = false;
    int is = S.size() <= 2 ? 0 : 1;
    int js = S.size() <= 1 ? 0 : 1;

    for (int i = is; i < cnt.size() && !ok; i++) {
        for (int j = js; j < cnt.size() && !ok; ++j) {
            for (int k = 1; k < cnt.size() && !ok; ++k) {
                VI needed(10, 0);
                ++needed[i];
                ++needed[j];
                ++needed[k];

                bool suf = true;
                for (int a = 0; a < 10; ++a) {
                    if (needed[a] > cnt[a]) {
                        suf = false;
                        break;
                    }
                }

                if (suf) {
                    int val = i*100 + j*10 + k;

                    if (val % 8 == 0) {
                        ok = true;
                        break;
                    }
                }
            }
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}