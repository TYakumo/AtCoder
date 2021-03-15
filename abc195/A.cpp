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
    int M;
    int H;
    cin >> M >> H;

    cout << (H%M == 0 ? "Yes" : "No") << endl;

    return 0;
}