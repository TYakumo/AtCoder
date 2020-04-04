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
    int A, B, C;
    cin >> A >> B >> C;

    swap(A, B);
    swap(A, C);

    cout << A << " " << B << " " << C << endl;
    return 0;
}