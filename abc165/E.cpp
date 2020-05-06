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
#include <queue>
using namespace std;

void outputPattern(int length, int offset) {
    int times = length/2;

    for (int i = 0; i < times; ++i) {
        cout << (i+offset+1) << " " << (length-i+offset) << endl;
    }
}

int main() {
    int N;
    int M;
    cin >> N >> M;

    outputPattern(M, 0);
    outputPattern(M+1, M);

    return 0;
}