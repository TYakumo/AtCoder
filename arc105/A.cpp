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
    vector <long long> num(4);

    for (int i = 0; i < 4; ++i) {
        cin >> num[i];
    }

    sort(num.begin(), num.end());

    if (num[1] + num[2] == num[0] + num[3] || num[1] + num[2] + num[0] == num[3] ) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}