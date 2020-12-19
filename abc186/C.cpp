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

string toDec(int v) {
    stringstream ss;
    string ret;
    ss << v;
    ss >> ret;

    return ret;
}

string toOct(int v) {
    stringstream ss;
    string ret;
    ss << std::oct << v;
    ss >> ret;

    return ret;
}

bool containsSeven(const string& str) {
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '7') {
            return true;
        }
    }

    return false;
}

int main() {

    int N;
    cin >> N;

    int ans = 0;
    for (int v = 1; v <= N; ++v) {
        string dstr = toDec(v);
        string ostr = toOct(v);

        if (!containsSeven(dstr) && !containsSeven(ostr)) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}