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

int main() {
    int N;
    cin >> N;

    VLL A(N);
    VLL B(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    long long sum = 0;

    for (int i = 0; i < N; ++i) {
        sum += A[i] * B[i];
    }

    cout << (sum == 0 ? "Yes" : "No") << endl;

    return 0;
}