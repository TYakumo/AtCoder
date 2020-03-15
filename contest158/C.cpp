#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    int A;
    int B;
    cin >> A >> B;

    // ceiling(0.08 P) >= A
    // ceiling(0.1 P) >= B
    // => P >= (A/0.08), P >= (B/0.1)

    const double eps = 1e-8;
    int LOW1 = (int)(A / 0.08 + eps);
    int LOW2 = (int)(B / 0.1 + eps);
    int MAXLOW = max(LOW1, LOW2);

    int ans = -1;
    for (int now = MAXLOW; true; ++now) {
        int TA = (int)(now * 0.08);
        int TB = (int)(now * 0.1);

        if (TA == A && TB == B) {
            ans = now;
            break;
        } else if (TA > A || TB > B) {
            break;
        }
    }

    cout << ans << endl;


    return 0;
}