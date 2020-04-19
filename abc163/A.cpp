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

int main() {
    const double pi = acos(-1);
    double R;
    cin >> R;

    printf("%.8f\n", 2*R*pi);

    return 0;
}