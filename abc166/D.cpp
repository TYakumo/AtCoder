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

inline long long lpow(long long b, long long p) {
    long long res = 1;

    for (int i = 1; i <= p; ++i) {
        res *= b;
    }

    return res;
}

int main() {
    long long X;
    cin >> X;

    bool found = false;

    for (long long A = -500; A <= 500 && !found; ++A) {
        for (long long B = -500; B < A; ++B) {
            long long res = lpow(A, 5) - lpow(B, 5);

            if (res == X) {
                cout << A << " " << B << endl;
                found = true;
                break;
            }
        }
    }


    return 0;
}