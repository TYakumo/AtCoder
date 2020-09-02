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
    int H1;
    int M1;
    int H2;
    int M2;
    int K;

    cin >> H1 >> M1 >> H2 >> M2 >> K;

    int delta = (H2-H1) * 60 + (M2 - M1);
    delta = abs(delta);

    cout << max(0, delta - K) << endl;

    return 0;
}