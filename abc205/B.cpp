#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int N;
    cin >> N;

    UMI cnt;
    for (int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        ++cnt[v];
    }

    bool ok = true;
    for (int v = 1; v <= N; ++v) {
        if (cnt[v] != 1) {
            ok = false;
            break;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;


    return 0;
}