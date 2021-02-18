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

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

int main() {
    int N;
    cin >> N;

    VI A(N);
    unordered_set <int> vSet;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());
    int minv = A[0];
    vSet.insert(A[0]);
    unordered_map <int, int> fSet;

    for (int i = 0; i < N; ++i) {
        unordered_set <int> DSet;
        int sq = sqrt(A[i]);
        for (int d = 1; d <= sq; ++d) {
            if (A[i] % d == 0) {
                int q = A[i]/d;
                DSet.insert(d);
                DSet.insert(q);
            }
        }

        auto iter = DSet.begin();

        while (iter != DSet.end()) {
            if (*iter < minv) {
                int q = A[i]/(*iter);

                if (fSet.count(*iter) == 0) {
                    fSet[*iter] = q;
                } else {
                    fSet[*iter] = gcd(fSet[*iter], q);
                }
            }
            ++iter;
        }
    }

    auto iter = fSet.begin();

    while (iter != fSet.end()) {
        if (iter->second == 1) {
            vSet.insert(iter->first);
        }
        ++iter;
    }

    cout << vSet.size() << endl;

    return 0;
}