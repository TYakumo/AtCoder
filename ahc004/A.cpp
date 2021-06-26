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

bool cmpLen(const pair<string, int> & a, const pair <string, int> & b) {
    // return a.second * b.first.size() < b.second * a.first.size();
    return a.first.size() < b.first.size();
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
    VSI tmp = gene;
    gene.clear();
    for (int i = 0; i < tmp.size(); ++i) {
        bool failed = false;

        for (int j = 0; j < tmp.size(); ++j) {
            if (i != j && tmp[i].first.size() <= tmp[j].first.size()) {
                auto iter = tmp[j].first.find(tmp[i].first);
                if (iter != string::npos) {
                    failed = true;
                    break;
                }
            }
        }

        if (!failed) {
            gene.push_back(tmp[i]);
        }
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
                string res2 = comb(gene[j].first, gene[i].first);

                if (res2.size() < res.size()) {
                    res = res2;
                }

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
    // sort(gene.begin(), gene.end(), cmpLen);

    VS ans(N);
    int idx = 0;
    int rcnt = gene.size();

    for (int i = 0; i < gene.size(); ++i) {
        if (ans[idx].size() + gene[i].first.size() <= N) {
            ans[idx] += gene[i].first;
            gene[i].second = 0;
            --rcnt;
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

    sort(gene.begin(), gene.end(), cmpLen);
    // cerr << "RCNT " << rcnt << endl;
    int last = N-1;
    int st = 0;

    for (int i = 0; i < gene.size(); ++i) {
        if (gene[i].second != 0) {
            bool ok = false;

            while (last >= 0 && !ok) {
                if (st+gene[i].first.size() > N) {
                    --last;
                    st = 0;
                } else {
                    ok = true;
                    for (int j = 0; j < gene[i].first.size(); ++j) {
                        if (ans[st+j][last] != '.') {
                            ok = false;
                            break;
                        }
                    }

                    if (ok) {
                        break;
                    } else {
                        --last;
                        st = 0;
                    }
                }
            }

            cerr << "WHY " << i << " " << last << endl;

            if (ok) {
                for (int j = 0; j < gene[i].first.size(); ++j) {
                    ans[st++][last] = gene[i].first[j];
                }
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}