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
    bool win = true;
    string S;
    cin >> S;

    for (int i = 1; i < S.size(); ++i) {
        if (S[0] != S[i]) {
            win = false;
            break;
        }
    }

    cout << (win ? "Won" : "Lost") << endl;

    return 0;
}