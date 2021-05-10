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
    long long N;
    int K;
    cin >> N >> K;

    for (int i = 0; i < K; ++i) {
        if (N%200 == 0) {
            N /= 200;
        } else {
            N *= 1000;
            N += 200;
        }
    }

    cout << N << endl;

    return 0;
}