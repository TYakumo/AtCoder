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
    string s;

    cin >> s;
    string output = (s[2] == s[3] && s[4] == s[5]) ? "Yes" : "No";
    cout << output  << endl;

    return 0;
}