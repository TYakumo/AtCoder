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
    int A;
    int B;
    int W;
    cin >> A >> B >> W;
    W *= 1000;

    if (A == B) {
        if (W%A != 0) {
            cout << "UNSATISFIABLE" << endl;
        } else {
            cout << W/A << " " << W/B << endl;
        }
    } else {
        bool failed = false;
        int diff = B-A;
        int minNum = (W+B-1)/B;
        int minRemain = W - minNum*B;
        if (minRemain > 0 || minRemain + diff*minNum < 0) {
            failed = true;
        }

        int maxNum = W/A;
        int maxRemain = W-maxNum*A;
        if (maxRemain > maxNum*diff) {
            failed = true;
        }


        if (failed) {
            cout << "UNSATISFIABLE" << endl;
        } else {
            cout << minNum << " " << maxNum << endl;
        }
    }



    return 0;
}