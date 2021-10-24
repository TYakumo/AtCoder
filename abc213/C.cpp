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

void label(map<int, int>& vMap) {
    int cnt = 1;

    auto iter = vMap.begin();
    while (iter != vMap.end()) {
        iter->second = cnt++;
        ++iter;
    }
}

int main() {
    int H;
    int W;
    int N;
    cin >> H >> W >> N;
    VVI P(N, VI(2));

    map <int, int> rowMap;
    map <int, int> colMap;

    for (int i = 0; i < N; ++i) {
        cin >> P[i][0] >> P[i][1];
        rowMap[P[i][0]] = 1;
        colMap[P[i][1]] = 1;
    }

    label(rowMap);
    label(colMap);

    for (int i = 0; i < N; ++i) {
        cout << rowMap[P[i][0]] << " " << colMap[P[i][1]] << endl;
    }

    return 0;
}