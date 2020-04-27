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
#include <queue>
using namespace std;

struct Edge {
    int to;
    int timeCost;
    int silverCost;
    Edge() {
    }

    Edge(int pt, int ptc, int psc) : to(pt), timeCost(ptc), silverCost(psc) {
    }
};

struct Node {
    int now;
    int silver;
    long long timeCost;
    Node() {
    }

    Node(int n, int s, long long t) : now(n), silver(s), timeCost(t) {
    }

    bool operator<(const Node& n) const {
        return timeCost > n.timeCost; // reverse pq order
    }
};

using VLL = vector <long long>;
using VVLL = vector< VLL >;

using VI = vector <int>;
using VVI = vector< VI >;

using VE = vector<Edge>;
using VVE = vector<VE>;

const long long INF = 1000000LL * 1000000000LL;

int main() {
    int N;
    int M;
    int S;

    cin >> N >> M >> S;

    VVE adja(N);

    VI goldSilver(N);
    VI goldTime(N);

    for (int i = 0; i < M; ++i) {
        int from;
        int to;
        int T;
        int C;
        cin >> from >> to >> C >> T;
        --from;
        --to;
        adja[from].emplace_back(Edge(to, T, C));
        adja[to].emplace_back(Edge(from, T, C));
    }

    for (int i = 0; i < N; ++i) {
        cin >> goldSilver[i] >> goldTime[i];
    }

    const int UPPER = 50;
    int MAXSILV = UPPER*N + UPPER;

    VVLL best(N, VLL(MAXSILV + 1, INF));

    priority_queue < Node > pq;
    pq.push(Node(0, min(S, MAXSILV), 0));
    best[0][min(S, MAXSILV)] = 0;

    while (!pq.empty()) {
        Node now = pq.top();
        pq.pop();
        int nowv = now.now;

        if (now.timeCost > best[nowv][now.silver]) {
            continue;
        }

        for (int i = 0; i < adja[nowv].size(); ++i) {
            int nextv = adja[nowv][i].to;

            for (int j = 0; true; ++j) {
                int newS = now.silver + j*(long long)goldSilver[nowv];
                long long timeCost = best[nowv][now.silver] + j*(long long)goldTime[nowv];

                if (newS <= MAXSILV || j == 0) {
                    int nnewS = newS - adja[nowv][i].silverCost;
                    if (nnewS < 0) {
                        continue;
                    }
                    long long nnewT = timeCost + adja[nowv][i].timeCost;

                    if (nnewT < best[nextv][nnewS]) {
                        best[nextv][nnewS] = nnewT;
                        pq.push(Node(nextv, nnewS, nnewT));
                    }
                } else {
                    break;
                }
            }
        }
    }

    for (int i = 1; i < N; ++i) {
        long long minVal = INF;
        for (int j = 0; j <= MAXSILV; ++j) {
            minVal = min(minVal, best[i][j]);
        }

        cout << minVal << endl;
    }

    return 0;
}