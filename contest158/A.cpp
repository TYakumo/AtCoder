#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    string str;

    cin >> str;
    int cnt[2] = {0, 0};

    for (int i = 0; i < str.size(); ++i) {
        ++cnt[str[i]-'A'];
    }

    if (cnt[0] && cnt[1]) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}