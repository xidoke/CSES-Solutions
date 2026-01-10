#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    scanf("%d", &N);
    for (int k = 1; k <= N; k++) {
        ull attacks = 4*(k-1)*(k-2);
        ull total = 1ull*k*k*(k*k-1)/2;
        printf("%llu\n", total - attacks);
    }
}