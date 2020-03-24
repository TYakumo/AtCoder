#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int N;
    cin >> N;

    bool pass = true;

    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;

        if (num%2 == 0) {
            if (num%3 != 0 && num%5 != 0) {
                pass = false;
                break;
            }
        }
    }

    cout << (pass ? "APPROVED" : "DENIED") << endl;

    return 0;
}