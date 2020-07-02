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
    long long N;

    cin >> N;
    string str;

    while (N) {
        long long val = (N-1)%26;
        str += (val + 'a');

        ++val;
        N -= val;
        N /= 26;
    }

    reverse(str.begin(), str.end());
    cout << str << endl;

    return 0;
}