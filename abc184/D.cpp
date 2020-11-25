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

using VI = vector<int>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;

double solve(VVVD& prob, VI num) {
    if (num[2] == 100) {
        return 0;
    }

    if (prob[num[0]][num[1]][num[2]] >= 0) {
        return prob[num[0]][num[1]][num[2]];
    }

    double &ret = prob[num[0]][num[1]][num[2]];
    ret = 0;

    VD P(3);
    double tot = num[0] + num[1] + num[2];

    for (int i = 0; i < 3; ++i) {
        VI newn = num;
        ++newn[i];
        sort(newn.begin(), newn.end());

        P[i] = num[i];
        P[i] /= tot;

        ret += P[i] * (solve(prob, newn) + 1);
    }

    return ret;
}

int main() {
    int A;
    int B;
    int C;

    cin >> A >> B >> C;

    VI num = {A, B, C};
    sort(num.begin(), num.end());
    VVVD prob(101, VVD(101, VD(101, -1)));

    cout << setprecision(15) << fixed << solve(prob, num) << endl;

    return 0;
}