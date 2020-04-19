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
    long long N;
    int M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int A;
        cin >> A;

        N -= A;
    }

    cout << (N >= 0 ? N : -1) << endl;

    return 0;
}