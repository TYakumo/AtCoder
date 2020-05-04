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

inline void judge(vector <int>& num, vector <int>& cntType, vector<char>& cho, int c1, int c2, int cp, int idx, int target) {
    const char ch[3] = {'A', 'B', 'C'};
    int N = cho.size();

    if (num[c1] > num[c2]) {
        --num[c1];
        ++num[c2];
        cho[idx] = ch[c2];
    } else if (num[c2] > num[c1]) {
        ++num[c1];
        --num[c2];
        cho[idx] = ch[c1];
    } else {
        if (idx+1 < N && num[cp] == 0) { // peeking
            if (cntType[idx+1] == target) {
                ++num[c1];
                --num[c2];
                cho[idx] = ch[c1];
            } else {
                --num[c1];
                ++num[c2];
                cho[idx] = ch[c2];
            }
        } else {
            ++num[c1];
            --num[c2];
            cho[idx] = ch[c1];
        }
    }
}

int main() {
    int N;
    vector <int> num(3);
    cin >> N >> num[0] >> num[1] >> num[2];

    vector <int> cntType(N);

    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;

        if (s == "AB") {
            cntType[i] = 0;
        } else if(s == "AC") {
            cntType[i] = 1;
        } else {
            cntType[i] = 2;
        }
    }

    vector <char> cho(N);
    bool failed = false;

    for (int i = 0; i < N; ++i) {
        if (cntType[i] == 0) { // AB
            judge(num, cntType, cho, 0, 1, 2, i, 1);
        } else if(cntType[i] == 1) { // AC
            judge(num, cntType, cho, 0, 2, 1, i, 0);
        } else { // BC
            judge(num, cntType, cho, 1, 2, 0, i, 0);
        }

        for (int j = 0; j < 3; ++j) {
            if (num[j] < 0) {
                failed = true;
                break;
            }
        }
    }

    if (failed) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        for (int i = 0; i < N; ++i) {
            cout << cho[i] << endl;
        }
    }

    return 0;
}