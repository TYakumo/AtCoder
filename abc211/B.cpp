#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;

using VS = vector <string>;

int main() {
    VS S(4);
    for (int i = 0; i < 4; ++i) {
        cin >> S[i];
    }

    bool failed = false;
    for (int i = 0; i < 4 && !failed; ++i) {
        for (int j = 0; j < 4 ; ++j) {
            if (i != j && S[i] == S[j]) {
                failed = true;
                break;
            }
        }
    }

    cout << (failed ? "No" : "Yes") << endl;
    return 0;
}