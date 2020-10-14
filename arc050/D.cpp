#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;

class SuffixArray {
    string str;
    VVI rank;
    VI finalRank;
    int logLevel;

    void rankInitialization() {
        // use mapping F(c) if customized dictionary order is needed
        const int CHARMAX = 256;
        vector<int> charCnt(CHARMAX);
        vector<int> charMap(CHARMAX);

        for (int i = 0; i < str.size(); ++i) {
            charCnt[str[i]] = 1;
        }

        int acc = 0;
        for (int i = 0; i < CHARMAX; ++i) {
            if (charCnt[i]) {
                charMap[i] = acc;
                ++acc;
            }
        }

        for (int i = 0; i < str.size(); ++i) {
            rank[0][i] = charMap[str[i]];
        }
    }

    inline int cmp(int i, int j, int l) {
        // sorting => s[i][l]+s[i+(1<<l)][l] vs s[j][l]+s[j+(l<<l)][l]
        if (rank[l][i] != rank[l][j]) {
            return rank[l][i] - rank[l][j];
        }

        int ni = i + (1<<l);
        int nj = j + (1<<l);

        if (ni >= str.size() && nj >= str.size()) {
            return 0;
        } else if (ni >= str.size()) { // j > i
            return -1;
        } else if (nj >= str.size()) { // i > j
            return 1;
        }

        return rank[l][ni] - rank[l][nj];
    }

    void sortArr(vector<int>& arr, int s, int e, int l) {
        if (s >= e) {
            return ;
        }

        int pivot = (s+e) / 2;
        int cnt = 0;
        int flag = 0;

        swap(arr[s], arr[pivot]);

        for (int i = s+1; i <= e; ++i) {
            int cmpRes = cmp(arr[s], arr[i], l-1);
            if (cmpRes > 0) {
                swap(arr[s+(++cnt)], arr[i]);
            } else if (cmpRes == 0) {
                // evenly distributed
                if (flag) {
                    swap(arr[s+(++cnt)], arr[i]);
                }
                flag ^= 1;
            }
        }

        swap(arr[s], arr[s+cnt]);
        sortArr(arr, s, s+cnt-1, l);
        sortArr(arr, s+cnt+1, e, l);
    }

    void computeRank() {
        vector <int> arr(str.size());
        for (int i = 0; i < str.size(); ++i) {
            arr[i] = i;
        }

        // level sorting
        for (int l = 1; l <= logLevel; ++l) {
            sortArr(arr, 0, arr.size()-1, l);

            int cnt = 1;
            rank[l][arr[0]] = 0;

            for (int i = 1; i < arr.size(); ++i) {
                if (cmp(arr[i], arr[i-1], l-1) != 0) {
                    rank[l][arr[i]] = cnt++;
                } else {
                    rank[l][arr[i]] = rank[l][arr[i-1]];
                }
            }
        }

        for (int i = 0; i < str.size(); ++i) {
            finalRank[rank[logLevel][i]] = i;
        }
    }

public:
    SuffixArray(string& s) {
        str = s;
        logLevel = 1;

        while ((1<<logLevel) < str.size()) {
            ++logLevel;
        }

        rank = move(VVI(logLevel+1, VI(str.size())));
        finalRank = move(vector<int>(str.size()));
    }

    static SuffixArray* buildSuffixArray(string& s) {
        SuffixArray* sa = new SuffixArray(s);
        sa->rankInitialization();
        sa->computeRank();

        return sa;
    }

    int getRankByLevel(int idx, int level) {
        return rank[level][idx];
    }

    int getRankIdx(int rank) {
        if (rank < str.size()) {
            return finalRank[rank];
        }

        return -1;
    }

    int getStrSize() {
        return str.size();
    }

    int getLogLevel() {
        return logLevel;
    }
};

SuffixArray* sa;

pair <int, int> cmpOnce(int i, int j) {
    int s = sa->getStrSize();
    int sign = 1;

    if (s-i < s-j) {
        swap (i, j);
        sign = -1;
    }

    int minlen = s-j;
    int ret = minlen;

    while (minlen > 0) {
        int l = 31-__builtin_clz(minlen);
        int msb = 1 << l;
        if (sa->getRankByLevel(i, l) != sa->getRankByLevel(j, l)) {
            return make_pair((sa->getRankByLevel(i, l) - sa->getRankByLevel(j, l)) * sign, ret);
        }

        i += msb;
        j += msb;
        minlen -= msb;
    }

    return make_pair(0, ret);
}

int cmpIdx(int i, int j) {
    int s = sa->getStrSize();
    int ni = i;
    int nj = j;

    int icnt = 0;
    int jcnt = 0;

    while (icnt < 2 && jcnt < 2) {
        pair <int, int> ret = cmpOnce(ni, nj);
        if (ret.first != 0) {
            return ret.first;
        }

        ni += ret.second;
        nj += ret.second;

        if (ni >= s) {
            ni = j;
            ++icnt;
        }

        if (nj >= s) {
            nj = i;
            ++jcnt;
        }
    }

    return 0;
}

bool intCmp(int a, int b) {
    return cmpIdx(a, b) < 0;
}

int main() {
    int N;
    string str;
    cin >> N >> str;

    sa = SuffixArray::buildSuffixArray(str);

    string ret;
    VI ans(N);

    for (int i = 0; i < N; ++i) {
        ans[i] = i;
    }

    sort(ans.begin(), ans.end(), intCmp);

    for (int i = 0; i < N; ++i) {
        printf("%d\n", ans[i]+1);
    }

    return 0;
}