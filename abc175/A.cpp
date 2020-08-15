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
    int R = 0;
    int MAXR = 0;

    for (int i = 0; i < S.size(); ++i) {
        if (S[i] == 'R') {
            ++R;
        } else {
            R = 0;
        }

        MAXR = max(MAXR, R);
    }

    cout << MAXR << endl;

    return 0;
}