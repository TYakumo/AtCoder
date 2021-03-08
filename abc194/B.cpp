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
    VI B(N);

    int ans = 1000000;
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        ans = min(ans, A[i]+B[i]);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            ans = min(ans, min(max(A[i], B[j]), max(A[j], B[i])));
        }
    }

    cout << ans << endl;


    return 0;
}