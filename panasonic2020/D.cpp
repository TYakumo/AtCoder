#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

void solve(int depth, int len, char maxc, vector<char>& arr) {
    if (depth == len) {
        for (int i = 0; i < arr.size(); ++i) {
            printf("%c", arr[i]);
        }
        printf("\n");

        return ;
    }

    for (char ch = 'a'; ch <= maxc; ++ch) {
        arr[depth] = ch;
        solve(depth+1, len, max((char)(ch+1), maxc), arr);
    }
}

int main() {

    int N;
    cin >> N;

    vector <char> arr(N);
    solve(0, N, 'a', arr);

    return 0;
}