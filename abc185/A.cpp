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
    int C;
    int D;

    cin >> A >> B >> C >> D;

    cout << min(min(A, B), min(C, D)) << endl;

    return 0;
}