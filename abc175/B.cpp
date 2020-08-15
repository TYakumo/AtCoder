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

    vector <int> L(N);

    for (int i = 0; i < N; ++i) {
        cin >> L[i];
    }

    sort(L.begin(), L.end());
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            if (L[j] == L[i]) {
                continue;
            }
            for (int k = j+1; k < N; ++k) {
                if (L[k] == L[j]) {
                    continue;
                }
                if (L[k] < L[j] + L[i]) {
                    ++ans;
                }
            }
        }
    }

    cout << ans << endl;


    return 0;
}