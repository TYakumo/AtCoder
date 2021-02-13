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
using VLL = vector <int>;

int main() {
    int N;
    int X;

    cin >> N >> X;

    VLL A;

    for (int i = 0; i < N; ++i) {
        int v;
        cin >> v;

        if (v != X) {
            A.push_back(v);
        }
    }

    for (int i = 0; i < A.size(); ++i) {
        if (i) {
            cout << " ";
        }

        cout << A[i];
    }

    cout << endl;



    return 0;
}