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

    vector <int> a(N);
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];

        if ((i%2 == 0) && a[i]%2) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}