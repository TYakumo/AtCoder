#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;
const int MAXS = 1000010;
const int MAXT = 2;
char str[MAXT][MAXS];

inline int countTwo(int n) {
    int ret = 0;

    while (n%2 == 0 && n) {
        n /= 2;
        ++ret;
    }

    return ret;
}

int main() {
    int N;

    scanf("%d", &N);
    scanf("%s", str[0]);

    int mulFactor = 2;

    for (int i = 1; i < MAXT && i < 2; ++i) {
        int len = N-i;

        for (int j = 0; j < len; j++) {
            int diff = abs(str[i-1][j+1] - str[i-1][j]);
            if (diff == 1) {
                mulFactor = 1;
            }
            str[i][j] = (diff + '0');
        }

        str[i][len] = '\0';
    }

    int len = N - 1;

    int result = 0;
    int twoCount = 0;

    if (mulFactor == 2) {
        for (int i = 0; i < len; ++i) {
            str[1][i] = (str[1][i]/2) + '0';
        }
    }

    for (int i = 0; i < len; ++i) {

        if (twoCount == 0) {
            result = (result + (str[1][i]-'0')%2)%2;
        }

        twoCount += countTwo(len-i-1);
        twoCount -= countTwo(i+1);
    }

    cout << result * mulFactor << endl;

    return 0;
}