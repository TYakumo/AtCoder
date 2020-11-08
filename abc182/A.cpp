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
    int A;
    int B;
    cin >> A >> B;

    int C = 2*A + 100;

    cout << max(0, (C-B)) << endl;

    return 0;
}