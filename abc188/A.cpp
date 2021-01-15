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
    int X;
    int Y;
    cin >> X >> Y;

    if (X >= Y) {
        swap (X, Y);
    }

    if (X < Y && X+3 > Y) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}