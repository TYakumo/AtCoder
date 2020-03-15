#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;
const int INF = 100000000;

int solve(string& A, string& B, string& C) {
    vector<int> ABMatch(A.size());
    vector<int> BCMatch(B.size());
    vector<int> ACMatch(A.size());

    // A precalculation
    for (int i = A.size()-1; i >= 0; --i) {
        bool pass = true;
        int l = A.size()-i;
        for (int j = 0; j < l && j < B.size(); ++j) {
            if (A[i+j] != B[j] && B[j] != '?' && A[i+j] != '?') {
                pass = false;
                break;
            }
        }
        ABMatch[i] = pass;

        pass = true;
        for (int j = 0; j < l && j < C.size(); ++j) {
            if (A[i+j] != C[j] && A[i+j] != '?' && C[j] != '?') {
                pass = false;
                break;
            }
        }
        ACMatch[i] = pass;
    }

    //B precalculation
    for (int i = B.size()-1; i >= 0; --i) {
        bool pass = true;
        int l = B.size()-i;

        for (int j = 0; j < l && j < C.size(); ++j) {
            if (B[i+j] != C[j] && B[i+j] != '?' && C[j] != '?') {
                pass = false;
                break;
            }
        }

        BCMatch[i] = pass;
    }

    int ans = A.size() + B.size() + C.size();
    // B start
    for (int a = 0; a < A.size(); ++a) {
        // B C no intersection
        if (ABMatch[a]) {
            int len = A.size();
            len = max(len, a+(int)B.size());
            ans = min(ans, len + (int)C.size());
        } else {
            continue;
        }

        // C start
        for (int b = 0; b < B.size(); ++b) {
            bool AC = true;

            // if intersect then check AC Match
            if (a+b < A.size()) {
                AC = ACMatch[a+b];
            }

            if (AC && ABMatch[a] && BCMatch[b]) {
                int len = A.size();
                len = max(len, a+(int)B.size());
                len = max(len, a+b+(int)C.size());
                ans = min(ans, len);
            }
        }

        // C in A, not in B
        for (int b = a+B.size(); b < A.size(); ++b) {
            if (ABMatch[a] && ACMatch[b]) {
                int len = A.size();
                len = max(len, b+(int)C.size());
                ans = min(ans, len);
            }
        }
    }

    //A B no intersection
    for (int b = 0; b < B.size(); ++b) {
        if (BCMatch[b]) {
            int len = B.size();
            len = max(len, b+(int)C.size());
            ans = min(ans, len + (int)A.size());
        }
    }

    return ans;
}

int main() {
    string A;
    string B;
    string C;

    int ans = INF;

    cin >> A >> B >> C;

    ans = min(ans, solve(A, B, C));
    ans = min(ans, solve(A, C, B));
    ans = min(ans, solve(B, A, C));
    ans = min(ans, solve(B, C, A));
    ans = min(ans, solve(C, A, B));
    ans = min(ans, solve(C, B, A));

    cout << ans << endl;

    return 0;
}