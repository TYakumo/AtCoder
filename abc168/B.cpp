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
    int K;
    string S;

    cin >> K >> S;

    if (K < S.size()) {
        S = S.substr(0, K);
        S += "...";
    }

    cout << S << endl;

    return 0;
}