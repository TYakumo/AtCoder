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
    int Q;

    cin >> N;
    long long sum = 0;
    unordered_map <long long, int> valMap;

    for (int i = 0; i < N; ++i) {
        long long v;
        cin >> v;
        ++valMap[v];
        sum += v;
    }

    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        long long B;
        long long C;
        cin >> B >> C;

        long long tot = valMap[B];
        sum -= B * tot;

        valMap[B] = 0;
        valMap[C] += tot;
        sum += C * tot;

        cout << sum << endl;
    }

    return 0;
}