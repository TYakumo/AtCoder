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
using PQI = long long;
using MAXPQ = priority_queue<PQI>;
using MINPQ = priority_queue<PQI, vector<PQI>, greater<PQI>>;

void addLeft(PQI v, MINPQ& pos, MAXPQ& neg, PQI& minVal) {
    if (pos.empty()) {
        neg.push(v);
        return ;
    }

    PQI posMin = pos.top();
    pos.push(v);
    PQI newPosMin = pos.top();
    pos.pop();

    // update minVal
    PQI dist = v - posMin;
    minVal += max(0LL, dist);

    neg.push(newPosMin);
}

void addRight(PQI v, MINPQ& pos, MAXPQ& neg, PQI& minVal) {
    if (neg.empty()) {
        pos.push(v);
        return ;
    }

    PQI negMax = neg.top();
    neg.push(v);
    PQI newNegMax = neg.top();
    neg.pop();

    // update minVal
    PQI dist = negMax - v;
    minVal += max(0LL, dist);

    pos.push(newNegMax);
}

void addAbs(PQI v, MINPQ& pos, MAXPQ& neg, PQI& minVal) {
    addLeft(v, pos, neg, minVal);
    addRight(v, pos, neg, minVal);
}

int main() {

    int N;
    cin >> N;

    PQI shift = 0;
    PQI minVal = 0;
    MINPQ pos;
    MAXPQ neg;
    VLL A(N);

    for (int i = 0; i < N; ++i) {
        PQI diff = 0;
        cin >> A[i];

        if (i) {
            diff = max(0LL, A[i] - A[i-1]);
        }
        shift += diff;

        addAbs(0-shift, pos, neg, minVal);
        addAbs(A[i]-shift, pos, neg, minVal);
    }

    cout << minVal << endl;

    return 0;
}