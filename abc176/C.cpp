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

int main() {
    int N;

    cin >> N;

    vector <int> A(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    long long sum = 0;

    for (int i = 1; i < N; ++i) {
        sum += max(0, A[i-1]-A[i]);
        A[i] = max(A[i], A[i-1]);
    }

    cout << sum << endl;

    return 0;
}