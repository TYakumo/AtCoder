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

    bool ok = true;
    for (int i = 0; i < S.size(); ++i) {
        if (i%2) {
            if (!(S[i] >= 'A' && S[i] <= 'Z')) {
                ok = false;
                break;
            }
        } else {
            if (!(S[i] >= 'a' && S[i] <= 'z')) {
                ok = false;
                break;
            }
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}