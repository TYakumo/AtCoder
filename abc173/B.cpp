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
    int N;
    cin >> N;
    map <string, int> cnt;

    for (int i = 0; i < N; ++i) {
        string j;
        cin >> j;
        ++cnt[j];
    }

    cout << "AC x " << cnt["AC"] << endl;
    cout << "WA x " << cnt["WA"] << endl;
    cout << "TLE x " << cnt["TLE"] << endl;
    cout << "RE x " << cnt["RE"] << endl;

    return 0;
}