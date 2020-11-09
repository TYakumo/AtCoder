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

    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        long long A;
        long long B;

        cin >> A >> B;

        long long len = B-A+1;

        ans += (A+B) * len / 2;
    }

    cout << ans << endl;

    return 0;
}