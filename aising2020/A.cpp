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
    int L;
    int R;
    int d;

    cin >> L >> R >> d;

    cout << (R/d) - (L-1)/d << endl;
    return 0;
}