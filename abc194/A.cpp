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

    int flag = 4;

    if (A+B >= 15 && B >= 8) {
        flag = 1;
    } else if (A+B >= 10 && B >= 3) {
        flag = 2;
    } else if (A+B >= 3) {
        flag = 3;
    }

    cout << flag << endl;

    return 0;
}