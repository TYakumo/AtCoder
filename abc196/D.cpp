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
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VVVLL = vector <VVLL>;
using VVVVLL = vector <VVVLL>;

long long solve(VVVVLL& dp, int H, int W, int w, int a, int b, int st) {
    long long &ret = dp[w][a][b][st];
    if (ret >= 0) {
        return ret;
    }

    int upper = 1<<H;
    if ((st&(upper-1)) == upper-1) {
        return ret = solve(dp, H, W, w+1, a, b, st/upper);
    }

    if (st == 0 && a == 0 && b == 0) {
        return 1;
    }

    if (w >= W) {
        return 0;
    }

    ret = 0;

    int upperst = 0;
    for (int s = 0; s < 2*H; ++s) {
        if ((1 << s) & st) {
            upperst = s;
        }
    }

    if (b > 0) {
        for (int o = 0; o < 2; ++o) {
            for (int h = 0; h < H; ++h) {
                int news = 1 << (o*H + h);
                if ((o*H + h) < upperst) {
                    continue;
                }

                if ((st & news) == 0) {
                    ret += solve(dp, H, W, w, a, b-1, st | news);
                }
            }
        }
    }

    if (a > 0) {
        // horizontal
        for (int h = 0; h < H; ++h) {
            int news = (1 << (H + h)) | (1 << h);
            if ((H + h) < upperst) {
                continue;
            }

            if ((st & news) == 0) {
                ret += solve(dp, H, W, w, a-1, b, st | news);
            }
        }

        // vertical
        for (int o = 0; o < 2; ++o) {
            for (int h = 0; h < H-1; ++h) {
                int news = (1 << (o*H + h)) | (1 << (o*H + h+1));
                if ((o*H + h+1) < upperst) {
                    continue;
                }

                if ((st & news) == 0) {
                    ret += solve(dp, H, W, w, a-1, b, st | news);
                }
            }
        }
    }

    return ret;
}

int main() {
    int H;
    int W;
    int A;
    int B;
    cin >> H >> W >> A >> B;

    const int MAXF = 17;
    VLL fact(MAXF);
    fact[0] = fact[1] = 1;

    for (int v = 2; v < MAXF; ++v) {
        fact[v] = fact[v-1] * v;
    }

    if (H > W) {
        swap(H, W);
    }

    long long ans = 0;


    if (H == 1) {
        // (A+B)!/A!/B!
        ans = fact[A+B] / fact[A] / fact[B];
    } else {
        // W*A*B*2^8
        VVVVLL dp(W+1, VVVLL(A+1, VVLL(B+1, VLL(256, -1))));
        ans = solve(dp, H, W, 0, A, B, 0);
    }

    cout << ans << endl;

    return 0;
}