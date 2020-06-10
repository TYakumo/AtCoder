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

vector <string> getNum(string str) {
    vector <string> ret;
    string last;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '.') {
            if (last.size()) {
                ret.push_back(last);
            }
            last = "";
        } else {
            last += str[i];
        }
    }

    if (last.size()) {
        ret.push_back(last);
    }

    return ret;
}

int main() {
    long long A;
    string B;

    cin >> A >> B;
    vector <string> nums = getNum(B);

    long long res = 0;
    res += A * atoll(nums[0].c_str());
    res += A * atoll(nums[1].c_str()) / 100;

    cout << res << endl;

    return 0;
}