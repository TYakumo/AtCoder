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
    int N;
    cin >> N;

    VI num(N);
    for (int i = 0; i < N; ++i) {
        cin >> num[i];
    }

    set <int> cand;
    for (int i = 0; i < num.size(); ++i) {
        if (i+1 < num.size() && num[i] > num[i+1]) {
            cand.insert(i);
        }
    }

    VI ans;
    bool ok = true;

    for (int i = 1; i < N; ++i) {
        if (!cand.empty()) {
            auto iter = cand.begin();
            int cpos = *iter;
            cand.erase(iter);

            swap(num[cpos], num[cpos+1]);
            ans.push_back(cpos);

            // check cpos-1, cpos
            if (cpos-1 >= 0) {
                if (num[cpos-1] > num[cpos]) {
                    cand.insert(cpos-1);
                } else { // need to erase cand
                    auto iter2 = cand.find(cpos-1);

                    if (iter2 != cand.end()) {
                        cand.erase(iter2);
                    }
                }
            }
            // check cpos+1, cpos+2
            if (cpos+2 < num.size()) {
                if (num[cpos+2] < num[cpos+1]) {
                    cand.insert(cpos+1);
                } else { // need to erase cand
                    auto iter2 = cand.find(cpos+1);

                    if (iter2 != cand.end()) {
                        cand.erase(iter2);
                    }
                }
            }
        } else {
            ok = false;
            break;
        }
    }

    for (int i = 1; i < N; ++i) {
        if (num[i] < num[i-1]) {
            ok = false;
        }
    }

    if (ok) {
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i]+1 << endl;
        }
    } else {
        cout << -1 << endl;
    }

    return 0;
}