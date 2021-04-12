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

string ItoS(long long N) {
    stringstream ss;
    string ret;
    ss << N;
    ss >> ret;
    return ret;
}

long long trimZero(long long val) {
    if (val == 0) {
        return val;
    }

    while (val%10 == 0) {
        val /= 10;
    }

    return val;
}


int main() {
    long long N;

    cin >> N;

    N = trimZero(N);
    string S = ItoS(N);

    bool ok = true;
    for (int i = 0; i < S.size()/2; ++i) {
        if (S[i] != S[S.size()-1-i]) {
            ok = false;
            break;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}