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

int main() {
    long long N;
    long long X;
    int M;
    cin >> N >> X >> M;
    // Sigma A^0 + A^2 + A^4 + A^8 + A^16 + A^32 ...
    long long res = 0;
    long long fpr = X;
    VLL idx(M, -1);
    VLL val(M+1, -1);

    for (long long i = 0; i < N; ++i) {

        if (idx[fpr] != -1) {
            long long len = i - idx[fpr];
            long long sum = 0;

            for (int j = idx[fpr]; j < i; ++j) {
                sum += val[j];
            }

            long long remain = N - i;
            long long blks = remain/len;
            res += sum * blks;

            for (long long j = i+blks*len; j < N; ++j) {
                res += fpr;
                fpr = fpr*fpr%M;
            }

            break;
        }

        idx[fpr] = i;
        val[i] = fpr;
        res += fpr;
        fpr = fpr*fpr%M;
    }

    cout << res << endl;

    return 0;
}