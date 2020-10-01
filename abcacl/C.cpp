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
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    int N;
    int M;

    cin >> N >> M;

    dsu d(N);
    int ans = 0;

    for (int i = 0; i < M; ++i) {
        int A;
        int B;
        cin >> A >> B;

        if (!d.same(--A, --B)) {
            d.merge(A, B);
            ++ans;
        }
    }

    cout << (d.groups().size()-1) << endl;

    return 0;
}