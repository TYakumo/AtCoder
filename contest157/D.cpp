#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <cstdio>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

class DisjointSet {
    VI parent;
    VI groupSize;
public:
    DisjointSet(int treeSize) {
        parent = move(VI(treeSize, -1));
        groupSize = move(VI(treeSize, 1));
    }

    int groupSizeOfN(int n) {
        return groupSize[findParent(n)];
    }

    int findParent(int n) {
        if (parent[n] == -1) {
            return n;
        }

        return parent[n] = findParent(parent[n]);
    }

    void unionGroup(int a, int b) {
        a = findParent(a);
        b = findParent(b);

        if (a != b) {
            if (groupSize[a] < groupSize[b]) {
                swap(a, b);
            }

            groupSize[a] += groupSize[b];
            parent[b] = a;
        }
    }
};

int main() {
    int N;
    int M;
    int K;
    scanf("%d %d %d", &N, &M, &K);

    DisjointSet ds(N);
    vector<vector <int>> blkCand(N); // check if block count is in the group
    vector <int> friCnt(N);

    for (int i = 0; i < M; ++i) {
        int a;
        int b;
        scanf("%d %d", &a, &b);
        --a;
        --b;
        ds.unionGroup(a, b);
        ++friCnt[a];
        ++friCnt[b];
    }

    for (int i = 0; i < K; ++i) {
        int a;
        int b;
        scanf("%d %d", &a, &b);
        --a;
        --b;
        blkCand[a].push_back(b);
        blkCand[b].push_back(a);
    }

    string str;
    for (int i = 0; i < N; ++i) {
        int groupCount = ds.groupSizeOfN(i) - friCnt[i] - 1;
        int groupParent = ds.findParent(i);

        for (int j = 0; j < blkCand[i].size(); ++j) {
            int cand = blkCand[i][j];
            if (ds.findParent(cand) == groupParent) {
                --groupCount;
            }
        }

        printf("%s%d", str.c_str(), groupCount);
        str = " ";
    }
    printf("\n");

    return 0;
}