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

int main() {
    int N;
    cin >> N;

    VI A(N);

    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // Sigma Ai^2 + Aj^2 - 2*Ai*Aj
    // t*Ai^2 + sigma Aj^2 - 2Ai*Aj
    long long ASum = 0;
    long long ASqSum = 0;
    long long times = 0;

    for (int i = 0; i < N; ++i) {
        sum -= 2 * A[i] * ASum;
        sum += ASqSum;
        sum += times * (A[i]*A[i]);

        ++times;
        ASum += A[i];
        ASqSum += A[i]*A[i];
    }

    cout << sum << endl;

    return 0;
}