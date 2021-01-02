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

using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VI = vector <int>;
using VVI = vector <VI>;

void visit(const VVI& adja, int now, int p, VI& parent) {
    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (nextv != p) {
            parent[nextv] = now;
            visit(adja, nextv, now, parent);
        }
    }
}

void visitSum(const VVI& adja, const VLL& vsum, int now, int p, long long sum, VI& parent, VLL& tot) {
    sum += vsum[now];
    tot[now] = sum;

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];

        if (nextv != p) {
            parent[nextv] = now;
            visitSum(adja, vsum, nextv, now, sum, parent, tot);
        }
    }
}

int main() {
    int N;
    cin >> N;

    VVI adja(N);
    VI parent(N, -1);
    VLL vsum(N);
    VLL tot(N);
    VVI edges(N-1);

    for (int i = 1; i < N; ++i) {
        int a;
        int b;
        cin >> a >> b;
        --a;
        --b;
        edges[i-1] = {a, b};
        adja[a].push_back(b);
        adja[b].push_back(a);
    }

    visit(adja, 0, -1, parent);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        int t;
        int e;
        long long x;
        cin >> t >> e >> x;
        --e;
        int a = edges[e][0];
        int b = edges[e][1];
        if (t == 2) {
            swap(a, b);
        }

        if (parent[a] == b) {
            vsum[a] += x;
        } else { // parent[b] == a
            vsum[0] += x;
            vsum[b] -= x;
        }
    }

    visitSum(adja, vsum, 0, -1, 0, parent, tot);

    for (int i = 0; i < tot.size(); ++i) {
        cout << tot[i] << endl;
    }

    return 0;
}