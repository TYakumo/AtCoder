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

    vector <int> sum(N);

    for (int i = 1; i < N; ++i) {
        int B;
        cin >> B;
        ++sum[B-1];
    }

    for (int i = 0; i < N; ++i) {
        cout << sum[i] << endl;
    }

    return 0;
}