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
    set <string> strSet;
    int N;
    cin >> N;

    while (N--) {
        string str;
        cin >> str;
        strSet.insert(str);
    }

    cout << strSet.size() << endl;

    return 0;
}