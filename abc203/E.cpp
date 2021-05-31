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
    int M;
    cin >> N >> M;

    int U = 2*N+1;
    map<int, int> ok;
    map <int, VI> pawn;
    set <int> xset;

    for (int i = 0; i < M; ++i) {
        int x;
        int y;
        cin >> x >> y;

        pawn[x].push_back(y);
        xset.insert(x);
    }

    ok[N] = 1;

    auto iter = pawn.begin();

    while (iter != pawn.end()) {
        VI nextOne;
        VI nextZero;
        for (int j = 0; j < iter->second.size(); ++j) {
            int y = iter->second[j];
            bool trigger = false;

            if (y-1 >= 0 && ok[y-1] == 1) {
                nextOne.push_back(y);
            }

            if (y+1 < U && ok[y+1] == 1) {
                nextOne.push_back(y);
            }

            if (!trigger) {
                nextZero.push_back(y);
            }
        }

        for (int j = 0; j < nextZero.size(); ++j) {
            ok[nextZero[j]] = 0;
        }

        for (int j = 0; j < nextOne.size(); ++j) {
            ok[nextOne[j]] = 1;
        }
        ++iter;
    }


    int sum = 0;
    auto iter2 = ok.begin();

    while (iter2 != ok.end()) {
        sum += iter2->second;
        ++iter2;
    }

    cout << sum << endl;

    return 0;
}