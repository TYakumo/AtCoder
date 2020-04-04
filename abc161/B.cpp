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
    int M;
    cin >> N >> M;

    vector <int> votes(N);

    int sum = 0;

    for (int i = 0; i < N; ++i) {
        cin >> votes[i];
        sum += votes[i];
    }

    int select = 0;

    for (int i = 0; i < N; ++i) {
        // votes[i] >= tot / 4M
        if (votes[i]*4*M >= sum) {
            ++select;
        }
    }

    cout << (select >= M ? "Yes" : "No") << endl;

    return 0;
}