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

vector <double> toCoor(int L, double deg) {
    vector <double> ret(2);

    ret[0] = cos(deg) * L;
    ret[1] = sin(deg) * L;

    return ret;
}

double getDist(vector<double>& A, vector<double>& B) {
    double dx = A[0] - B[0];
    double dy = A[1] - B[1];

    return sqrt(dx*dx + dy*dy);
}

int main() {
    int A;
    int B;
    int H;
    int M;

    cin >> A >> B >> H >> M;
    const double PI = acos(-1.0);

    double mDeg = M/60.0 * 2*PI;
    double hDeg = (H/12.0 + M/720.0) * 2*PI;

    vector <double> mCoor = toCoor(A, mDeg);
    vector <double> hCoor = toCoor(B, hDeg);

    cout << setprecision(12) << fixed << getDist(mCoor, hCoor) << endl;

    return 0;
}