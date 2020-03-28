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

int main() {
    int X;
    int Y;
    int A;
    int B;
    int C;
    long long sum = 0;

    cin >> X >> Y >> A >> B >> C;

    vector <int> red(A);
    vector <int> green(B);
    vector <int> noc(C);

    for (int i = 0; i < A; ++i) {
        cin >> red[i];
    }

    for (int i = 0; i < B; ++i) {
        cin >> green[i];
    }

    for (int i = 0; i < C; ++i) {
        cin >> noc[i];
    }


    sort(red.begin(), red.end(), greater<int>());
    sort(green.begin(), green.end(), greater<int>());
    sort(noc.begin(), noc.end(), greater<int>());
    int offset[3] = {0, 0, 0};

    while (X && Y) {
        int redChoice = offset[0] < red.size() ? red[offset[0]] : -1;
        int greenChoice = offset[1] < green.size() ? green[offset[1]] : -1;
        int nocChoice = offset[2] < noc.size() ? noc[offset[2]] : -1;

        if (nocChoice > max(redChoice, greenChoice)) {
            int redEnd = offset[0]+X-1 < red.size() ? red[offset[0]+X-1] : -1;
            int greenEnd = offset[1]+Y-1 < green.size() ? green[offset[1]+Y-1] : -1;

            if (redEnd < greenEnd) {
                --X;
                sum += noc[offset[2]++];
            } else {
                --Y;
                sum += noc[offset[2]++];
            }
        } else {
            if (redChoice > greenChoice) {
                --X;
                sum += red[offset[0]++];
            } else {
                --Y;
                sum += green[offset[1]++];
            }
        }
    }

    while (X) {
        int redChoice = offset[0] < red.size() ? red[offset[0]] : -1;
        if (offset[2] < noc.size() && noc[offset[2]] > redChoice) {
            sum += noc[offset[2]++];
        } else {
            sum += red[offset[0]++];
        }
        --X;
    }

    while (Y) {
        int greenChoice = offset[1] < green.size() ? green[offset[1]] : -1;
        if (offset[2] < noc.size() && noc[offset[2]] > greenChoice) {
            sum += noc[offset[2]++];
        } else {
            sum += green[offset[1]++];
        }
        --Y;
    }

    cout << sum << endl;

    return 0;
}