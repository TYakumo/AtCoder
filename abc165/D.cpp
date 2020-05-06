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
    long long N;

    cin >> A >> B >> N;
    // x = k*B + m
    // floor (Am/B)
    N = min(N, B-1);

    cout << (A*N) / B << endl;

    return 0;
}