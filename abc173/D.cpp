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

int main() {
    int N;
    cin >> N;
    vector <long long> comfort(N);

    for (int i = 0; i < N; ++i) {
        cin >> comfort[i];
    }

    sort(comfort.begin(), comfort.end(), greater<int>());

    priority_queue <long long> pq;
    pq.push(comfort[0]);
    long long ans = 0;

    for (int i = 1; i < N; ++i) {
        long long topVal = pq.top();
        ans += topVal;
        pq.pop();

        pq.push(comfort[i]);
        pq.push(comfort[i]);
    }

    cout << ans << endl;

    return 0;
}