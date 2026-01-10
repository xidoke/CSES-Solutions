#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
ll x, mx, sum;
int main() {
    scanf("%d", &N);
    scanf("%lld", &mx);
    for (int i = 1; i < N; i++) {
        scanf("%lld", &x);
        mx = max(mx, x);
        sum += mx - x;
    }
    printf("%lld\n", sum);
}