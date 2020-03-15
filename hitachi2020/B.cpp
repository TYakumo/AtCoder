#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    int A[2];
    int M;
    cin >> A[0] >> A[1] >> M;
    vector <int> arr[2];
    int total = 0;
    const int INF = 100000000;

    for (int i = 0; i < 2; ++i) {
        int minP = INF;

        arr[i] = vector<int>(A[i], 0);
        for (int j = 0; j < A[i]; ++j) {
            scanf("%d", &arr[i][j]);
            minP = min(minP, arr[i][j]);
        }

        total += minP;
    }

    for (int i = 0; i < M; ++i) {
        int x;
        int y;
        int c;

        scanf("%d %d %d", &x, &y, &c);

        --x;
        --y;
        int cost = max(0, arr[0][x] + arr[1][y] - c);
        total = min(total, cost);
    }

    cout << total << endl;

    return 0;
}