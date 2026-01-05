#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int t; cin >> t;
    while (t--) {
        ll x, y; cin >> y >> x;
        if (y == x) {
            cout << y*y - y + 1 << endl;
        }
        else if (y > x) {
            if (y&1) {
                cout << (y-1)*(y-1) + x << endl;
            }
            else {
                cout << y*y - x + 1 << endl;
            }
        }
        else {
            if (x&1) {
                cout << x*x - y + 1 << endl;
            }
            else {
                cout << (x-1)*(x-1) + y << endl;
            }
        }
    }

    return 0;
}