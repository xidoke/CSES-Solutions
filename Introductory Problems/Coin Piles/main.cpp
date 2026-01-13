#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int T;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        ll a, b; cin >> a >> b;
        if (max(a, b) > 2*min(a, b)) 
        {printf("NO\n");
        continue;
        }
        if ((a+b) % 3 == 0) {
            printf("YES\n");
            continue;
        }
        printf("NO\n");
    }
    return 0;
}