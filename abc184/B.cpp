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
    int X;
    cin >> N >> X;

    string S;

    cin >> S;

    for (int i = 0; i < S.size(); ++i) {
        int plus = S[i] == 'o' ? 1 : -1;
        X = max(0, X+plus);
    }

    cout << X << endl;

    return 0;
}