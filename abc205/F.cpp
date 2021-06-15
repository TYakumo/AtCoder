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
#include <atcoder/maxflow>
using namespace std;
using namespace atcoder;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int H;
    int W;
    int N;
    cin >> H >> W >> N;


    int V = H+W+2*N+2;
    int src = 0;
    int sink = V-1;

    mf_graph <int> g(V);

    for (int c = 0; c < W; ++c) {
        int cn = 1+2*N+H+c;
        g.add_edge(cn, sink, 1);
    }

    for (int r = 0; r < H; ++r) {
        int rn = 1+2*N+r;
        g.add_edge(src, rn, 1);
    }

    for (int i = 0; i < N; ++i) {
        int A;
        int B;
        int C;
        int D;
        cin >> A >> B >> C >> D;

        --A;
        --B;
        --C;
        --D;
        int qni = i+1;
        int qno = i+N+1;
        g.add_edge(qni, qno, 1);

        for (int r = A; r <= C; ++r) {
            int rn = 1+2*N+r;
            g.add_edge(rn, qni, 1);
            for  (int c = B; c <= D; ++c) {
                int cn = 1+2*N+H+c;

                g.add_edge(qno, cn, 1);
            }
        }
    }

    cout << g.flow(src, sink) << endl;

    return 0;
}