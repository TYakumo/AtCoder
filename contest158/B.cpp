#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    long long N;
    long long A;
    long long B;
    long long tot;

    cin >> N >> A >> B;
    tot = (A+B);

    long long now = N/tot;

    N -= now*tot;
    cout << now*A + min(N, A) << endl;

    return 0;
}