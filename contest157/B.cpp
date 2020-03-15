#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;
const int MAXR = 3;
int main() {
    VVI bingo(MAXR, VI(MAXR));

    for (int i = 0; i < MAXR; ++i) {
        for (int j = 0; j < MAXR; ++j) {
            cin >> bingo[i][j];
        }
    }

    int N;

    cin >> N;

    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;
        bool found = false;

        for (int r = 0; r < MAXR && !found; ++r) {
            for (int c = 0; c < MAXR; ++c) {
                if (bingo[r][c] == num) {
                    bingo[r][c] = -1;
                    found = true;
                    break;
                }
            }
        }

    }

    bool b = false;
    vector <int> row(MAXR);
    vector <int> col(MAXR);
    int diag[2] = {0, 0};

    for (int r = 0; r < MAXR; ++r) {
        for (int c = 0; c < MAXR; ++c) {
            if (bingo[r][c] == -1) {
                ++row[r];
                ++col[c];

                if (r == c) {
                    ++diag[0];
                }

                if (r == MAXR-c-1) {
                    ++diag[1];
                }
            }
        }
    }

    b = (diag[0] == MAXR) || (diag[1] == MAXR);

    for (int i = 0; i < MAXR; ++i) {
        if (row[i] == MAXR || col[i] == MAXR) {
            b = true;
        }
    }

    cout << (b ? "Yes" : "No") << endl;

    return 0;
}