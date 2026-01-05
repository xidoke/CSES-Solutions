#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2*10e5+1;
int main() {
    int n; cin >> n;
    int a[MAXN];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < max_val) {
            ans += max_val - a[i];
        }
        else {
            max_val = a[i];
        }
    }
    cout << ans << endl;
    return 0;
}