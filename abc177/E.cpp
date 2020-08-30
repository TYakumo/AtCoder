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

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

int main() {
    int N;
    cin >> N;

    const int MAXV = 1000000;
    const int SQMAXV = 1000;

    vector <int> A;
    vector <int> primes;
    vector <int> sqprimes;
    vector <bool> notPrime(MAXV+10);
    int g = -1;

    for (int v = 2; v <= MAXV; ++v) {
        if (!notPrime[v]) {
            primes.push_back(v);
            if (v <= SQMAXV) {
                sqprimes.push_back(v);
            }
        }

        for (int nv = v*2; nv <= MAXV; nv += v) {
            notPrime[nv] = true;
        }
    }

    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;

        if (g == -1) {
            g = val;
        } else {
            g = gcd(g, val);
        }

        if (val != 1) {
            A.push_back(val);
        }
    }

    if (g != 1) {
        cout << "not coprime" << endl;
    } else {
        // set or pairwise
        if (A.size() > primes.size()) {
            cout << "setwise coprime" << endl;
        } else {
            unordered_map <int, int> counter;

            for (int i = 0; i < A.size(); ++i) {
                int val = A[i];

                for (int j = 0; j < sqprimes.size() && sqprimes[j] <= val; ++j) {
                    int div = sqprimes[j];
                    if (val % div == 0) {
                        ++counter[div];
                        while (val % div == 0) {
                            val /= div;
                        }
                    }
                }

                if (val != 1) {
                    ++counter[val];
                }
            }

            bool failed = false;
            auto iter = counter.begin();

            while (iter != counter.end()) {
                if (iter->second >= 2) {
                    failed = true;
                    break;
                }
                ++iter;
            }

            if (failed) {
                cout << "setwise coprime" << endl;
            } else {
                cout << "pairwise coprime" << endl;
            }
        }
    }


    return 0;
}