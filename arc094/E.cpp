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
    long long sum = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        sum += A[i];
    }

    long long diff = sum;

    for (int i = 0; i < N; ++i) {
        if (A[i] > B[i]) {
            diff = min(diff, B[i]);
        }
    }

    cout << sum-diff << endl;

    return 0;
}