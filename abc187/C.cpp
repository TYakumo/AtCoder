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

using VS = vector <string>;
int main() {
    int N;
    cin >> N;

    string failed;
    set <string> sset;
    set <string> nsset;

    for (int i = 0; i < N; ++i) {
        string str;
        cin >> str;
        bool neg = false;

        if (str[0] == '!') {
            str = str.substr(1, str.size()-1);
            neg = true;
        }

        if (neg) {
            if (sset.count(str)) {
                failed = str;
            }
            nsset.insert(str);
        } else {
            if (nsset.count(str)) {
                failed = str;
            }
            sset.insert(str);
        }
    }

    if (failed == "") {
        failed = "satisfiable";
    }

    cout << failed << endl;





    return 0;
}