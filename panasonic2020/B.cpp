#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    int R;
    int C;

    cin >> R >> C;

    long long tot = (long long)R*C;

    if (min(R, C) > 1) {
        cout << (tot+1)/2 << endl;
    } else {
        cout << 1 << endl;
    }

    return 0;
}