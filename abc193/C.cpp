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
    cin >> N;

    long long sq = sqrt(N);

    long long ok = 0;
    unordered_set <long long> covered;
    for (long long v = 2; v <= sq; ++v) {
        if (covered.find(v) != covered.end()) {
            continue;
        }
        long long now = v*v;

        while (now <= N) {
            ++ok;
            covered.insert(now);
            now *= v;
        }
    }

    cout << N-ok << endl;


    return 0;
}