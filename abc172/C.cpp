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
    vector <int> vSize(2);
    long long K;

    cin >> vSize[0] >> vSize[1] >> K;

    vector< vector <int> > A(2);
    vector< vector <long long> > acc(2);

    for (int i = 0; i < 2; ++i) {
        A[i] = vector<int>(vSize[i]);
        acc[i] = vector<long long>(vSize[i]+1);

        for (int j = 0; j < vSize[i]; ++j) {
            cin >> A[i][j];
            acc[i][j+1] = acc[i][j] + A[i][j];
        }
    }

    int ans = 0;

    for (int i = 0; i <= vSize[0]; ++i) {
        if (acc[0][i] > K) {
            break;
        }

        int low = 0;
        int up = vSize[1];
        int mid = 0;
        int best = 0;

        while (low <= up) {
            mid = (low + up) / 2;

            if (acc[1][mid] + acc[0][i] <= K) {
                best = mid;
                low = mid+1;
            } else {
                up = mid-1;
            }
        }

        ans = max(ans, i+best);
    }

    cout << ans << endl;

    return 0;
}