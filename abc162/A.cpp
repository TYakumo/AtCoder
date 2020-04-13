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
    int N;
    cin >> N;
    bool seven = false;

    while (N) {
        if (N%10 == 7) {
            seven = true;
            break;
        }

        N /= 10;
    }

    cout << (seven ? "Yes" : "No") << endl;
    return 0;
}