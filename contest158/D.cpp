#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;
const int MAXS = 100010;
char str[MAXS];

int main() {
    int r = 0; // reverse
    deque <char> strQue;

    scanf("%s", str);
    for (int i = 0; str[i]; ++i) {
        strQue.push_back(str[i]);
    }

    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int T;
        scanf("%d", &T);

        if (T == 1) {
            r ^=  1;
        } else {
            int F;
            char ch;
            scanf("%d %c", &F, &ch);
            --F;

            F ^= r;

            if (F == 0) {
                strQue.push_front(ch);
            } else {
                strQue.push_back(ch);
            }
        }
    }

    if (r) {
        reverse(strQue.begin(), strQue.end());
    }

    for (int i = 0; i < strQue.size(); ++i) {
        printf("%c", strQue[i]);
    }

    printf("\n");

    return 0;
}