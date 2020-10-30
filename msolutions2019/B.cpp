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
    cin >> S;

    int ans = 0;
    for (int i = 0; i < S.size(); ++i) {
        if (S[i] == 'o') {
            ++ans;
        }
    }

    cout << (ans+(15-S.size()) >= 8 ? "YES" : "NO") << endl;

    return 0;
}