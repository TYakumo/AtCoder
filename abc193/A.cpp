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

    cout << setprecision(12) << fixed << (double)(A-B)*100.0/A << endl;

    return 0;
}