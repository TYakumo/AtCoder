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
    vector <int> level(8);
    level[0] = 1800;
    level[1] = 1600;
    level[2] = 1400;
    level[3] = 1200;
    level[4] = 1000;
    level[5] = 800;
    level[6] = 600;
    level[7] = 400;

    int X;
    cin >> X;
    int ans = 9;

    for (int i = 0; i < level.size(); ++i) {
        if (X >= level[i]) {
            ans = i+1;
            break;
        }
    }

    cout << ans << endl;
    return 0;
}