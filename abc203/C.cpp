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


int main() {
    int N;
    long long K;
    cin >> N >> K;

    VVLL A(N, VLL(2));

    for (int i = 0; i < N; ++i) {
        cin >> A[i][0] >> A[i][1];
    }

    sort(A.begin(), A.end());
    long long now = 0;

    for (int i = 0; i < A.size(); ++i) {
        if (A[i][0] - now <= K) {
            K -= (A[i][0]-now);
            now = A[i][0];
            K += A[i][1];
        }
    }

    now += K;

    cout << now << endl;

    return 0;
}