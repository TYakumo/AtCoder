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

    int ans = 0;
    unordered_set <int> nset;

    for (int i = 0; i < N; ++i) {
        int p;
        cin >> p;

        nset.insert(p);
        while (nset.count(ans) > 0) {
            ++ans;
        }

        cout << ans << endl;
    }


    return 0;
}