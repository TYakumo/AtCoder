#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <unordered_map>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;
const int MAXS = 200010;

char str[MAXS];

int main() {
    int N;
    int P;
    scanf("%d %d", &N, &P);
    scanf("%s", str);

    long long ans = 0;

    // sub(i, j) / 10^(j-1) = (sub(i, end) - sub(j-1, end)) / 10^(j-1)
    // sub(i, j) / 10^(j-1) % P == 0
    // sub(i, j)%P == 0 if 10 co-prime P ( P != 2 and P != 5)

    if (P == 2 || P == 5) {
        int pCnt = 0;

        for (int i = N-1; i >= 0; --i) {
            if ((str[i]-'0')%P == 0) {
                ++pCnt;
            }

            ans += pCnt;
        }
    } else {
        int mul = 1;
        int sum = 0;
        vector<int> rCount(P, 0);

        rCount[0] = 1;

        for (int i = N-1; i >= 0; --i) {
            sum = (sum + (str[i] - '0') * mul) % P;
            // (sum - x) % P == 0
            // sum % P = x
            ans += rCount[sum];

            ++rCount[sum];
            mul *= 10;
            mul %= P;
        }
    }

    cout << ans << endl;

    return 0;
}