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
    long long n;
    cin >> n;

    long long low = 1;
    long long up = (long long) sqrt(2*n) + 500000;
    long long x = 0;

    while (low <= up) {
        long long mid = (low+up)/2;

        long long sum = mid*(mid+1)/2;

        if (sum <= (n+1)) {
            x = mid;
            low = mid+1;
        } else {
            up = mid-1;
        }
    }

    cout << (n-x+1) << endl;

    return 0;
}