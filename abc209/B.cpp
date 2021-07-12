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
    int X;
    cin >> N >> X;

    VI A(N);
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        sum += A[i];
        if (i%2 == 1) {
            --sum;
        }
    }

    cout << (X>=sum ? "Yes" : "No") << endl;

    return 0;
}