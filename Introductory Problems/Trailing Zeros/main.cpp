#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    ll ans = 0;
    for (ll i = 5; i <= n; i *= 5) {
        ans += n / i;
    }
    cout << ans << endl;
}