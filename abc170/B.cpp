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

    // A+B = X
    // 2*A + 4*B = Y
    // 2*A + 2*B = 2*X
    // Y - 2*X = 2*B

    int D = Y - 2*X;

    if (D >= 0 && D%2 == 0) {
        int B = D/2;
        int A = X-B;

        if (A >= 0 && B >= 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else {
        cout << "No" << endl;
    }

    return 0;
}