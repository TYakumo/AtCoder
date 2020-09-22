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
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;

class UnionAndFind {
    public:
    vector <int> groupSize;
    vector <int> groupParent;

    UnionAndFind (int gSize) {
        groupSize = vector<int> (gSize, 1);
        groupParent = vector<int> (gSize, -1);
    }

    int findGroup(int n) {
        if (groupParent[n] == -1) {
            return n;
        }
        return groupParent[n] = findGroup(groupParent[n]);
    }

    void unionGroup(int x, int y) {
        y = findGroup(y);
        x = findGroup(x);

        if (x == y) {
            return ;
        }

        if (groupSize[x] > groupSize[y]) {
            swap(x, y);
        }

        groupSize[y] += groupSize[x];
        groupParent[x] = y;
    }
};

int main() {
    int N;
    cin >> N;

    VVI coor(N, VI(3));

    for (int i = 0; i < N; ++i) {
        cin >> coor[i][0] >> coor[i][1];
        coor[i][2] = i;
    }

    sort(coor.begin(), coor.end());

    UnionAndFind group(N);
    const int INF = 1000000000;
    VI choice;
    choice.push_back(0);

    for (int i = 1; i < N; ++i) {
        if (choice.empty() || coor[i][1] < coor[choice.back()][1]) {
            choice.push_back(i);
        } else {
            int bestIdx = INF;

            while (!choice.empty() && coor[i][1] > coor[choice.back()][1]) {
                group.unionGroup(coor[choice.back()][2], coor[i][2]);
                if (bestIdx == INF) {
                    bestIdx = choice.back();
                }

                choice.pop_back();
            }

            if (bestIdx != INF) {
                choice.push_back(bestIdx);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << group.groupSize[group.findGroup(i)] << endl;
    }

    return 0;
}