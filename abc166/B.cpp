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
    int K;
    cin >> N >> K;
    vector <int> snuke (N);

    for (int i = 0; i < K; ++i) {
        int d;
        cin >> d;
        for (int j = 0; j < d; ++j) {
            int n;
            cin >> n;
            snuke[n-1] = 1;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (snuke[i] == 0) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}