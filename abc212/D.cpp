#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int Q;
    cin >> Q;
    priority_queue <long long, vector<long long>, greater<long long>> pq;
    long long base = 0;

    while (Q--) {
        int t;
        long long v;
        cin >> t;

        if (t == 3) {
            if (pq.empty()) {
                cout << base << endl;
            } else {
                cout << base + pq.top() << endl;
                pq.pop();
            }
        } else if (t == 2) {
            cin >> v;
            base += v;
        } else {
            cin >> v;
            pq.push(v-base);
        }
    }

    return 0;
}