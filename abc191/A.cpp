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
    int V;
    int T;
    int S;
    int D;

    cin >> V >> T >> S >> D;

    if (T*V > D || D > S*V) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}