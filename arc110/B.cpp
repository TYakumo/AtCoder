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
using VLL = vector <long long>;
using VVLL = vector <VLL>;

int main() {
    int N;
    string T;
    long long ans = 0;
    long long tot = 30000000000LL;

    cin >> N >> T;
    VI suffix(T.size(), -1);
    VLL needLength(3);

    string S = "110";
    int match = -1;
    for (int i = 1; i < T.size(); ++i) {
        while (match != -1 && T[match+1] != T[i]) {
            match = suffix[match];
        }

        if (T[match+1] == T[i]) {
            ++match;
        }

        suffix[i] = match;
    }

    VVLL appear(3, VLL(3*T.size()+1, -1));
    VLL sum(3*T.size()+10);

    long long cycle = 0;
    long long times = 0;
    long long cnt = 0;

    match = -1;
    long long start = 0;
    for (int i = 0; i <= 3*T.size(); ++i) {
        int now = i%S.size();

        while (match != -1 && T[match+1] != S[now]) {
            match = suffix[match];
        }

        if (T[match+1] == S[now]) {
            ++match;
        }

        if (appear[now][match+1] != -1) {
            long long remain = tot - i;
            cycle = i - appear[now][match+1];
            times = i > 0 ? sum[i-1] : 0;

            if (appear[now][match+1] > 0) {
                times -= sum[appear[now][match+1]-1];
            }

            ans += remain / cycle * times;
            break;
        } else {
            appear[now][match+1] = i;
        }

        if (match == T.size()-1) {
            match = suffix[match];
            ++ans;
            ++cnt;
        }

        sum[i] = cnt;
    }

    cout << ans << endl;

    return 0;
}