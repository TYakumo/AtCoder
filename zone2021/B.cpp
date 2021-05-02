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
    int TD;
    int TH;
    cin >> N >> TD >> TH;

    VI D(N);
    VI H(N);
    double maxh = 0;

    for (int i = 0; i < N; ++i) {
        cin >> D[i] >> H[i];
        double delta = TH - H[i];
        double ratio = D[i] / (double)(TD - D[i]);
        double total = delta + delta * ratio;

        double target = TH - total;
        maxh = max(maxh, target);
    }

    cout << setprecision(15) << fixed << maxh << endl;

    return 0;
}