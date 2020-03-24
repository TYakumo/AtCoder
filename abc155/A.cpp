#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
using namespace std;

bool poor(int A, int B, int C) {
    return (A==B) && (B!=C);
}

int main() {
    int A;
    int B;
    int C;

    cin >> A >> B >> C;

    if (poor(A, B, C) || poor(A, C, B) || poor(B, C, A)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}