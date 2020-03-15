#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

using VI = vector <int> ;
using VVI = vector <VI> ;

int main() {
    string str;
    cin >> str;

    if ((str.size() % 2) || str.size() < 2) {
        cout << "No" << endl;
    } else {
        bool pass = true;
        for (int i = 0; i < str.size(); i += 2) {
            if (str[i] != 'h') {
                pass = false;
                break;
            }

            if (str[i+1] != 'i') {
                pass = false;
                break;
            }
        }

        cout << (pass ? "Yes" : "No") << endl;
    }

    return 0;
}