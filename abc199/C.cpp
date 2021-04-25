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

int transformV(int v, int N, int fir, int sec) {
    if (v >= N) {
        return (v-N)+sec;
    } else {
        return v+fir;
    }
}

int main() {
    int N;
    string S;
    int Q;
    cin >> N >> S >> Q;

    int fir = 0;
    int sec = N;

    for (int q = 0; q < Q; ++q) {
        int t;
        int a;
        int b;
        cin >> t >> a >> b;
        --a;
        --b;

        if (t == 2) {
            fir = (fir + N)%(2*N);
            sec = (sec + N)%(2*N);
        } else {
            int ta = transformV(a, N, fir, sec);
            int tb = transformV(b, N, fir, sec);

            swap(S[ta], S[tb]);
        }
    }

    if (fir == N) { // final swap
        for (int i = 0; i < N; ++i) {
            swap(S[i], S[i+N]);
        }
    }

    cout << S << endl;

    return 0;
}