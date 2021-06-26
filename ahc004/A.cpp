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
using VS = vector <string>;
using VSI = vector <pair<string, int>>;

bool cmp(const pair<string, int> & a, const pair <string, int> & b) {
    return a.second * b.first.size() < b.second * a.first.size();
    // return a.first.size() < b.first.size();
}

string comb(const string& a, const string& b) {
    int maxlen = min(a.size(), b.size());
    for (int suf = maxlen; suf > 0; --suf) {
        bool pass = true;

        int start = a.size()-suf;
        for (int i = 0; i < suf; ++i) {
            if (a[start+i] != b[i]) {
                pass = false;
                break;
            }
        }

        if (pass) {
            return a.substr(0, a.size()-suf) + b;
        }
    }

    return a + b;
}

int main() {
    int N;
    int M;

    cin >> N >> M;

    VSI gene(M);
    for (int i = 0; i < M; ++i) {
        cin >> gene[i].first;
        gene[i].second = 1;
    }

    while (true) {
        bool changed = false;
        VI used(gene.size());
        VSI ngene;

        for (int i = 0; i < gene.size(); i++) {
            if (used[i]) {
                continue;
            }

            for (int j = i+1; j < gene.size(); ++j) {
                if (used[j]) {
                    continue;
                }

                string res = comb(gene[i].first, gene[j].first);
                if (res.size() <= N) {
                    used[i] = used[j] = 1;
                    changed = true;
                    ngene.push_back({res, gene[i].second + gene[j].second});
                    break;
                }
            }
        }

        if (!changed) {
            break;
        }

        for (int i = 0; i < gene.size(); ++i) {
            if (used[i] == 0) {
                ngene.push_back(gene[i]);
            }
        }
        gene = ngene;
    }

    sort(gene.begin(), gene.end(), cmp);

    VS ans(N);
    int idx = 0;

    for (int i = 0; i < gene.size(); ++i) {
        if (ans[idx].size() + gene[i].first.size() <= N) {
            ans[idx] += gene[i].first;
        } else {
            // fill in
            while (ans[idx].size() < N) {
                ans[idx] += ".";
            }
            ++idx;
        }

        if (idx == N) {
            break;
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}