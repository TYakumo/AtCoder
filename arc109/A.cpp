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
    int a;
    int b;
    int x;
    int y;

    cin >> a >> b >> x >> y;
    int ans = abs(a-b)*y + x;
    if (a > b) {
        ans = min(ans, abs(a-b-1)*y + x);
        ans = min(ans, (abs(a-b)*2-1)*x);
    } else {
        ans = min(ans, (abs(a-b)*2+1)*x);
    }

    cout << ans << endl;

    return 0;
}