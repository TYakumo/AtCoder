#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

class FenwickTree {
    VI sum;
public:
    FenwickTree (int treeSize) {
        sum = move(VI(treeSize+1));
    }

    void addVal(int idx, int val) {
        while (idx < sum.size()) {
            sum[idx] += val;
            idx += (idx & (-idx));
        }
    }

    int getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        int ret = 0;

        while (idx) {
            ret += sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    int queryRange(int a, int b) {
        return getVal(b) - getVal(a-1);
    }
};


const int MAXS = 500010;
char str[MAXS];

int main() {

    vector <FenwickTree*> ft;
    int N;
    int Q;

    scanf("%d", &N);
    scanf("%s", str);

    for (int i = 0; i < 26; ++i) {
        ft.push_back(new FenwickTree(N));
    }

    for (int i = 0; i < N; ++i) {
        int c = str[i] - 'a';
        ft[c]->addVal(i+1, 1);
    }

    scanf("%d", &Q);
    while (Q--) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int idx;
            char ch;
            scanf("%d %c", &idx, &ch);

            ft[str[idx-1]-'a']->addVal(idx, -1);
            ft[ch-'a']->addVal(idx, 1);
            str[idx-1] = ch;
        } else {
            int distinct = 0;
            int l;
            int r;
            scanf("%d%d", &l, &r);

            for (int i = 0; i < 26; ++i) {
                int v = ft[i]->queryRange(l, r);
                if (v) {
                    ++distinct;
                }
            }

            printf("%d\n", distinct);
        }
    }


    return 0;
}