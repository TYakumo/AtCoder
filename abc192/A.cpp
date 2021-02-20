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
    long long X;
    cin >> X;
    X %= 100;

    cout << (100-X) << endl;

    return 0;
}