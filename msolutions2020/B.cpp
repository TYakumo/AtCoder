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
    int C;
    int K;
    int need = 0;

    cin >> A >> B >> C;
    cin >> K;

    while (B <= A) {
        B *= 2;
        ++need;
    }

    while (C <= B) {
        C *= 2;
        ++need;
    }

    cout << (need <= K ? "Yes" : "No") << endl;
    return 0;
}