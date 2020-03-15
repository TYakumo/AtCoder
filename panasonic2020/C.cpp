#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <cmath>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    long long A;
    long long B;
    long long C;

    cin >> A >> B >> C;

    // A + 2*sqrt(A*B) + B < C
    // 2*sqrt(*A*B) < (C-B-A)
    // 4*A*B < (C-B-A)^2
    long long diff = C-B-A;
    if (4*A*B < diff*diff && diff > 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}