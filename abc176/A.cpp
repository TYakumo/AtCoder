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
    int N;
    int X;
    int T;

    cin >> N >> X >> T;

    cout << (N+X-1) / X * T << endl;

    return 0;
}