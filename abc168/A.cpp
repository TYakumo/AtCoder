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
    int V;
    cin >> V;

    if (V%10 == 3) {
        cout << "bon" << endl;
    } else if (V%10 == 0 || V%10 == 1 || V%10 == 6 || V%10 == 8) {
        cout << "pon" << endl;
    } else {
        cout << "hon" << endl;
    }

    return 0;
}