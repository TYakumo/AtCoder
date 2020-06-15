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

using VI = vector <int>;
using VVI = vector <VI>;

int main() {
    int N;
    int K;

    cin >> N >> K;

    vector <int> intensity(N);

    for (int i = 0; i < N; ++i) {
        cin >> intensity[i];
    }

    int nowTurn = 0;

    while (nowTurn < K) {
        vector <int> newIntensity(N);
        vector <int> intAcc(N+1);

        for (int i = 0; i < N; ++i) {
            int minInt = max(0, i - intensity[i]);
            int maxInt = min(N, i + intensity[i] + 1);


            ++intAcc[minInt];
            --intAcc[maxInt];
        }

        int now = 0;
        bool converged = true;
        for (int i = 0; i < N; ++i) {
            now += intAcc[i];
            newIntensity[i] = now;
            if (newIntensity[i] != N) {
                converged = false;
            }
        }

        ++nowTurn;
        intensity = newIntensity;

        if (converged) {
            break;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (i) {
            cout << " ";
        }
        cout << intensity[i];
    }

    cout << endl;

    return 0;
}