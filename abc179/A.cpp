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

    if (S.back() == 's') {
        S += "es";
    } else {
        S += "s";
    }

    cout << S << endl;

    return 0;
}