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
    long long A;
    long long B;
    long long V;
    long long W;
    long long T;

    cin >> A >> V;
    cin >> B >> W;
    cin >> T;

    long long D = abs(A-B);

    if (D == 0) {
        cout << "YES" << endl;
    } else if (V <= W) {
        cout << "NO" << endl;
    } else {
        long long DV = V - W;
        if (T*DV >= D) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }


    return 0;
}