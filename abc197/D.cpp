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

using VD = vector <double>;

int main() {
    int N;
    cin >> N;

    VD X(N);
    VD Y(N);

    for (int i = 0; i < 2; ++i) {
        cin >> X[i] >> Y[i];
    }

    double dx = X[1]-X[0];
    double dy = Y[1]-Y[0];
    double dist = sqrt(dx*dx+dy*dy);
    const double pi = acos(-1.0);
    double angle = (N-2)*180.0;
    double piAngle = (N-2)*pi / N;
    double sqdist = dist*sin(pi/2.0-piAngle/2);
    double ratio = sqdist / dist;

    piAngle *= -1/2.0;

    // transform
    double nvx = cos(piAngle) * dx - sin(piAngle) * dy;
    double nvy = sin(piAngle) * dx + cos(piAngle) * dy;
    nvx *= ratio;
    nvy *= ratio;

    cout << setprecision(15) << fixed << X[0]+nvx << " " << Y[0]+nvy << endl;

    return 0;
}