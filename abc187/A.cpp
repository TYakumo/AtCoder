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

int toSum(const string& S) {
    int ret = 0;
    for (int i = 0; i < S.size(); ++i) {
        ret += S[i]-'0';
    }
    return ret;
}

int main() {
    string A;
    string B;
    cin >> A >> B;

    cout << max(toSum(A), toSum(B)) << endl;

    return 0;
}