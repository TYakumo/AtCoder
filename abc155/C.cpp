#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    int N;

    map <string, int> voteCount;
    vector <string> ans;
    int maxCount = 0;

    cin >> N;
    for (int i = 0; i < N; ++i) {
        string str;
        cin >> str;

        maxCount = max(maxCount, ++voteCount[str]);
    }

    auto iter = voteCount.begin();
    while (iter != voteCount.end()) {
        if (iter->second == maxCount) {
            ans.push_back(iter->first);
        }
        ++iter;
    }

    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}