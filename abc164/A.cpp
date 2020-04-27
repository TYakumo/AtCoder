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
    int S;
    int W;
    cin >> S >> W;

    cout << (S > W ? "safe" : "unsafe") << endl;

    return 0;
}