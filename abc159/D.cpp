#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <unordered_map>
using namespace std;

int main() {
    int N;

    cin >> N;
    vector <int> val(N);
    unordered_map <int, int> cnt;

    for (int i = 0; i < N; ++i) {
        cin >> val[i];
        ++cnt[val[i]];
    }

    long long sum = 0;

    auto iter = cnt.begin();

    while (iter != cnt.end()) {
        sum += (iter->second * (iter->second - 1LL)) / 2;
        ++iter;
    }

    for (int i = 0; i < N; ++i) {
        long long vcnt = cnt[val[i]];

        cout << sum - (vcnt * (vcnt-1))/2 + (vcnt-1)*(vcnt-2)/2 << endl;
    }

    return 0;
}