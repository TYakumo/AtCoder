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

inline int toDir(char dir) {
    switch (dir) {
        case 'U': return 0;
        case 'D': return 1;
        case 'L': return 2;
        default : return 3;
    }
}

struct Point {
    int x;
    int y;
    int d;
    int s; // y - x
};

struct sorter {
    bool operator()(const Point& a, const Point& b) const {
        return a.s < b.s;
    }
};

struct sorterY {
    bool operator()(const Point& a, const Point& b) const {
        return a.y < b.y;
    }
};

struct sorterX {
    bool operator()(const Point& a, const Point& b) const {
        return a.x < b.x;
    }
};

using VP = vector <Point>;

void rotateBy90(VP& pnts) {
    const int newDirMapping[] = {3, 2, 0, 1};

    for (int i = 0; i < pnts.size(); ++i) {
        int tx = pnts[i].x;
        int ty = pnts[i].y;

        pnts[i].x = ty;
        pnts[i].y = -tx;
        pnts[i].d = newDirMapping[pnts[i].d];
        pnts[i].s = pnts[i].y - pnts[i].x;
    }
}

int main() {
    int N;

    cin >> N;

    VP points(N);

    for (int i = 0; i < N; ++i) {
        char ch;
        cin >> points[i].x >> points[i].y >> ch;
        points[i].s = points[i].y - points[i].x;
        points[i].d = toDir(ch);
    }

    const long long INF = 1000000000LL * 1000000000LL;
    long long ans = INF;

    for (int dir = 0; dir < 4; ++dir) {
        // opposite
        sort(points.begin(), points.end(), sorterY());
        for (int i = 0; i < N; ) {
            if (points[i].d != 2 && points[i].d != 3) {
                ++i;
                continue;
            }

            int end = i+1;
            VP target;
            target.push_back(points[i]);

            while (end < N) {
                if (points[end].y == points[i].y) {

                    if (points[i].d == 2 || points[i].d == 3) {
                        target.push_back(points[end]);
                    }

                    ++end;
                } else {
                    break;
                }
            }

            sort(target.begin(), target.end(), sorterX());
            for (int i = 1; i < target.size(); ++i) {
                if (target[i-1].d == 3 && target[i].d == 2) { // collision
                    long long timeNeeded = (target[i].x - target[i-1].x) * 5LL;
                    ans = min(ans, timeNeeded);
                }
            }

            i = end;
        }

        // by 90 degree
        sort(points.begin(), points.end(), sorter());

        for (int i = 0; i < N; ) {
            if (points[i].d != 1 && points[i].d != 3) {
                ++i;
                continue;
            }

            int end = i+1;
            VP target;
            target.push_back(points[i]);

            while (end < N) {
                if (points[end].s == points[i].s) {

                    if (points[i].d == 1 || points[i].d == 3) {
                        target.push_back(points[end]);
                    }

                    ++end;
                } else {
                    break;
                }
            }

            sort(target.begin(), target.end(), sorterX());
            for (int i = 1; i < target.size(); ++i) {
                if (target[i-1].d == 3 && target[i].d == 1) { // intersecting
                    long long timeNeeded = (target[i].x - target[i-1].x) * 10LL;
                    ans = min(ans, timeNeeded);
                }
            }

            i = end;
        }

        rotateBy90(points);
    }

    if (ans == INF) {
        cout << "SAFE" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}