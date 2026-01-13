#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int MOD = 1000000007;
int N;

ll fast_pow2(int x) {
    ll a = 2;
    ll ans = 1;
    while (x > 0) {
        if (x & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        x >>= 1;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    cout << fast_pow2(N) << endl;
    return 0;
}