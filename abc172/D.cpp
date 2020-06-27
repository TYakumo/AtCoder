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
    cin >> N;

    vector <long long> comb(N+1);
    vector <bool> notPrime(N+1);
    vector <int> primes;
    long long ans = 1;

    for (long long v = 2; v <= N; ++v) {
        if (!notPrime[v]) {
            comb[v] = 2;
            primes.push_back(v);
        }

        ans += v * comb[v];

        for (int i = 0; primes[i] * v <= N; ++i) {
            long long val = primes[i] * v;
            long long temp = val;

            notPrime[val] = true;

            // decomposition
            long long count = 0;
            while (temp % primes[i] == 0) {
                temp /= primes[i];
                ++count;
            }

            comb[val] = comb[v] * (count+1) / count;

            if (v % primes[i] == 0) {
                break;
            }
        }

    }

    cout << ans << endl;

    return 0;
}