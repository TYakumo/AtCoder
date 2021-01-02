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
    int N;
    cin >> N;

    VLL A(N);
    VLL B(N);
    VLL cho(N);
    long long ASum = 0;
    long long BSum = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        ASum += A[i];
        cho[i] = B[i]+2*A[i];
    }

    int idx = 0;
    sort(cho.begin(), cho.end(), greater<long long>());

    while (BSum <= ASum) {
        BSum += cho[idx];
        ++idx;
    }

    cout << idx << endl;

    return 0;
}