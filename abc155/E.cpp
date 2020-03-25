#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
using namespace std;

const int MAXS = 1000100;
char str[MAXS];

int main() {

    scanf("%s", str);
    int sum = 0;
    int len = 0;

    while (str[len] != 0) {
        sum += (str[len++] - '0');
    }

    int ans = sum;
    // pay = needed + return

    const int INF = 1000000000;
    vector<vector <int>> pay(len, vector<int>(3, INF)); // 0 => paid, 1 => needed, 2 => needed+1
    pay[len-1][0] = (str[len-1] - '0');
    pay[len-1][1] = 0;

    for (int i = len-2; i >= 0; --i) {

        // for 362 => needed 2: => 0, needed 0 => 2
        // needed 6: 0+2, needed 7: 8+0, needed 0: min(2+6, 7+8) = 8
        // needed 0: min(8+3, 4+2+4, 4+8+3) = 10,
        // 402 - 362 = 40
        int c = (str[i] - '0');
        int pc = (str[i+1] - '0');
        pay[i][0] = min(pay[i+1][0]+c, min(c+1+pay[i+1][1]+(10-pc), c+1+pay[i+1][2]+(10-pc-1)));
        pay[i][1] = pay[i+1][0];
        pay[i][2] = min(pay[i+1][2] + (10-pc-1), pay[i+1][1] + (10-pc));
    }

    int c = (str[0] - '0');
    cout << min(pay[0][0],  min(1 + pay[0][2] + (10-c-1), 1 + pay[0][1] + (10-c))) << endl;

    return 0;
}