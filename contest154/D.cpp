#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int N;
    int K;

    scanf("%d%d", &N, &K);

    std::vector <int> dices(N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &dices[i]);
    }

    int maxVal = 0; //max 2000000 * 1000
    int sum = 0;

    // expected value : (1 + .... p) / p = (1+p) * p / 2 / p = (1+p) / 2
    for (int i = 0; i < K; ++i) {
        sum += (dices[i] + 1);
    }

    maxVal = sum;

    for (int i = K; i < N; ++i) {
        sum -= (dices[i-K] + 1);
        sum += (dices[i] + 1);

        maxVal = max(maxVal, sum);
    }

    std::cout << std::setprecision(10) << maxVal / 2.0 << std::endl;
    return 0;
}