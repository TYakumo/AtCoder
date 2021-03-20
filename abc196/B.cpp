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
    string X;
    cin >> X;
    int len = 0;
    for (int i = 0; i < X.size(); ++i) {
        if (X[i] == '.') {
            break;
        }
        ++len;
    }

    cout << X.substr(0, len) << endl;
    return 0;
}