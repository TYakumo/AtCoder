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

    if (M > 0) {
        if (M+2 <= N) {
            int start = 2;
            for (int i = 0; i <= M; ++i) {
                cout << start << " " << start+2 << endl;
                start += 3;
            }
            cout << 1 << " " << start - 2 << endl;

            for (int i = M+2; i < N; ++i) {
                cout << start << " " << start + 1 << endl;
                start += 2;
            }
        } else {
            cout << -1 << endl;
        }
    } else if (M == 0) {
        int start = 1;
        for (int i = 0; i < N; ++i) {
            cout << start << " " << start+1 << endl;
            start += 2;
        }

    } else { // Takahashi is optimal
        cout << -1 << endl;
    }


    return 0;
}