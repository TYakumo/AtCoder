#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

void bsearch(long long target, long long curVal, vector<long long>&val, long long& rank) {
    int low = 0;
    int up = val.size()-1;
    int greater = -1;

    while (low <= up) {
        int mid = (low + up) / 2;
        long long res = curVal * val[mid];

        if (res <= target) {
            greater = mid;
            low = mid+1;
        } else {
            up = mid-1;
        }
    }

    rank += (greater+1);
}

int main() {
    int N;
    long long K;
    cin >> N >> K;

    vector <long long> val(N);
    vector <long long> rval(N);

    for (int i = 0; i < N; ++i) {
        cin >> val[i];
    }

    sort(val.begin(), val.end());
    rval = val;
    reverse(rval.begin(), rval.end());

    const long long INF = 1000000000000000000LL;
    long long low = -INF;
    long long up = INF;
    long long ans = INF;

    while (low <= up) {
        long long rank = 0; // how many numbers <= mid
        long long mid = (low+up) / 2;

        for (int i = 0; i < val.size(); ++i) {
            if (val[i]*val[i] <= mid) { //avoid self*self
                --rank;
            }

            if (val[i] < 0) {
                bsearch(mid, val[i], rval, rank);
            } else {
                bsearch(mid, val[i], val, rank);
            }
        }

        rank /= 2;

        if (rank >= K) {
            up = mid-1;
            ans = mid;
        } else {
            low = mid+1;
        }
    }

    cout << ans << endl;


    return 0;
}