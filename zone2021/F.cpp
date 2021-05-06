#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;


int main() {
    int N;
    int M;
    int arank = 0;
    cin >> N >> M;

    while ((1<<arank) < N) {
        ++arank;
    }

    VI OK(N+1, 1);

    for (int i = 0; i < M; ++i) {
        int tmp;
        cin >> tmp;
        OK[tmp] = 0;
    }

    VVI val;
    for (int i = 1; i < N; ++i) {
        if (OK[i]) {
            val.push_back({i, i});
        }
    }

    int rank = 0;

    for (int i = 0; i < arank; ++i) {
        int pivot = -1;

        for (int j = i; j < val.size(); ++j) {
            if (val[j][0] & (1<<i)) {
                pivot = j;
                break;
            }
        }

        if (pivot == -1) {
            break;
        }

        swap(val[pivot], val[i]);

        for (int j = i+1; j < val.size(); ++j) {
            if (val[j][0] & (1<<i)) {
                val[j][0] ^= val[i][0];
            }
        }
        ++rank;
    }

    if (arank == rank) {
        VVI sval;
        for (int i = 0; i < arank; ++i) {
            int cnt = 0;
            for (int j = 0; j < arank; ++j) {
                if (val[i][1]&(1<<j)) {
                    ++cnt;
                }
            }

            sval.push_back({cnt, val[i][1]});
        }

        sort(sval.begin(), sval.end());
        int now = 0;
        VI prevec;
        VVI ans;

        for (int i = 0; i < sval.size(); ++i) {
            VI newvec = prevec; // newvec = prevec + val[cho] + prevec

            int nextv = now ^ sval[i][1];
            ans.push_back({now, nextv});
            newvec.push_back(sval[i][1]);
            now = nextv;

            for (int j = 0; j < prevec.size(); ++j) {
                nextv = now ^ prevec[j];
                ans.push_back({now, nextv});
                now = nextv;
                newvec.push_back(prevec[j]);
            }

            prevec = newvec;
        }

        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i][0] << " " << ans[i][1] << endl;
        }
    } else {
        cout << "-1" << endl;
    }


    return 0;
}