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
    int sum = 0;

    for (int i = 0; i < S.size(); ++i) {
        sum += (S[i] - '0');
    }

    cout << (sum%9 == 0 ? "Yes" : "No") << endl;

    return 0;
}