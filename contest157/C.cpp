#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    int N;
    int M;

    cin >> N >> M;

    vector <int> val (N, -1);
    bool illegal = false;

    for (int i = 0; i < M; ++i) {
        int d;
        int v;
        cin >> d >> v;

        --d;
        if (val[d] == -1 || val[d] == v) {
            val[d] = v;
        } else { // contradicts
            illegal = true;
            break;
        }
    }

    if (val[0] == 0 && N > 1) {
        illegal = true;
    }

    if (illegal) {
        cout << -1 << endl;
    } else {
        if (val[0] == -1) {
            val[0] = N > 1 ? 1 : 0; // no leading zero
        }

        for (int i = 0; i < val.size(); ++i) {
            if (val[i] == -1) {
                cout << 0;
            } else {
                cout << val[i];
            }
        }
        cout << endl;
    }

    return 0;
}