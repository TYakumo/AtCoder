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
    string T;
    cin >> T;

    for (int i = 0; i < T.size(); ++i) {
        if (T[i] == '?') {
            T[i] = 'D';
        }
    }

    cout << T << endl;

    return 0;
}