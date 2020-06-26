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
    vector <int> x(5);
    int idx = 0;

    for (int i = 0; i < 5; ++i) {
        cin >> x[i];

        if (x[i] == 0) {
            idx = i + 1;
            break;
        }
    }

    cout << idx << endl;

    return 0;
}