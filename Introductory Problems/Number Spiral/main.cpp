#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int T;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    scanf("%d", &T);
    while (T--) {
        ll x, y; scanf("%lld %lld", &y, &x);
        ll k = max(x, y);
        ll base = (k - 1) * (k - 1);
        ll ans;

        if (k & 1) 
            if (y == k) ans = base + x;
            else        ans = k*k - y + 1;
        else 
            if (x == k) ans = base + y;
            else        ans = k*k - x + 1;
        cout << ans << '\n';
    }
}