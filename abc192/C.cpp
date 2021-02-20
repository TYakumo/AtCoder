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
#include <sstream>
using namespace std;

int calc(int N) {
    stringstream ss;
    ss << N;

    string s;
    string s1;
    ss >> s;
    sort(s.begin(), s.end());

    s1 = s;
    reverse(s1.begin(), s1.end());

    return atoi(s1.c_str()) - atoi(s.c_str());
}

int main() {
    int N;
    int K;
    cin >> N >> K;

    for (int i = 0; i < K; ++i) {
        N = calc(N);
    }

    cout << N << endl;

    return 0;
}