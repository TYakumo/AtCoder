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
    int D;
    int T;
    int S;

    cin >> D >> T >> S;

    if (S*T >= D) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}