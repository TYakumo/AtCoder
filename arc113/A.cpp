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
    long long K;
    cin >> K;

    long long ans = 0;
    for (long long C = 1; C <= K; ++C) {
        for (long long B = 1; B*C <= K; ++B) {
            for (long long A = 1; A*B*C <= K; ++A) {
                ++ans;
            }
        }
    }

    cout << ans << endl;

    return 0;
}