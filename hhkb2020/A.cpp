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
    string S;
    string T;
    cin >> S >> T;

    if (S == "Y") {
        for (int i = 0; i < T.size(); ++i) {
            cout << (char)toupper(T[i]) ;
        }
    } else {
        cout << T;
    }
    cout << endl;
    return 0;
}