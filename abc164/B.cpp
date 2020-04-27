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

    int T[2] = {(int)ceil((double)C/B), (int)ceil((double)A/D)};

    cout << (T[0] <= T[1] ? "Yes" : "No") << endl;

    return 0;
}