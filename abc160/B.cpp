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
    int N;

    cin >> N;

    cout << (N/500)*1000 + ((N%500)/5)*5 << endl;

    return 0;
}