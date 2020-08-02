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
    int K;

    cin >> K;
    vector <bool> remain(K+10);
    int now = 7;
    int counter = 1;
    bool appear = false;

    while (true) {
        now %= K;

        if (now == 0) {
            appear = true;
            break;
        } else if(remain[now]) { // loop
            break;
        }

        remain[now] = true;
        now *= 10;
        now += 7;
        ++counter;
    }


    if (appear) {
        cout << counter << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}