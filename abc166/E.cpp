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

    vector <int> H(N);
    unordered_map <int, int> counter;

    long long ans = 0;

    for (int i = 0; i < N; ++i) {
        cin >> H[i];
        ans += counter[(i+1)-H[i]-1];
        ++counter[i+H[i]];
    }

    cout << ans << endl;

    return 0;
}