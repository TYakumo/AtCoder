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
#include <deque>
using namespace std;

int main() {
    int K;
    int cnt = 0;

    deque <string> que;
    vector <string> ans;

    for (char ch = '1'; ch <= '9'; ++ch) {
        string str;
        str += ch;
        que.push_back(str);
        ans.push_back(str);
        ++cnt;
    }

    cin >> K;

    while (!que.empty() && cnt < K) {
        string str = que.front();
        que.pop_front();

        for (char ch = '0'; ch <= '9'; ++ch) {
            if (abs(ch - str[str.size()-1]) <= 1) {
                string news = str + ch;
                que.push_back(news);
                ans.push_back(news);
                ++cnt;
            }
        }
    }

    cout << ans[K-1] << endl;

    return 0;
}