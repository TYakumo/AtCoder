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
    string S;
    string T;

    cin >> S >> T;

    int ans = 0;

    for (int i = 0; i < S.size(); ++i) {
        if (S[i] != T[i]) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}