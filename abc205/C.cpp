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
    long long A;
    long long B;
    long long C;
    cin >> A >> B >> C;

    if (A == B) {
        cout << "=" << endl;
    } else if (abs(A) == abs(B)) {
        if (C%2 == 0) {
            cout << "=" << endl;
        } else {
            if (A < B) {
                cout << "<" << endl;
            } else {
                cout << ">" << endl;
            }
        }
    } else if (A < 0 && B < 0) {
        if (C%2 == 0) {
            if (A < B) {
                cout << ">" << endl;
            } else {
                cout << "<" << endl;
            }
        } else {
            if (A < B) {
                cout << "<" << endl;
            } else {
                cout << ">" << endl;
            }
        }
    } else if (A >= 0 && B >= 0) {
        if (A > B) {
            cout << ">" << endl;
        } else {
            cout << "<" << endl;
        }
    } else if (A < 0 && B >= 0) {
        if (C%2 == 0) {
            if (abs(A) > B) {
                cout << ">" << endl;
            } else {
                cout << "<" << endl;
            }
        } else {
            cout << "<" << endl;
        }
    } else { // A >= 0 && B < 0
        if (C%2 == 0) {
            if (abs(B) > A) {
                cout << "<" << endl;
            } else {
                cout << ">" << endl;
            }
        } else {
            cout << ">" << endl;
        }
    }

    return 0;
}