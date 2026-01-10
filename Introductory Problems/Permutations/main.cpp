#include <bits/stdc++.h>
using namespace std;
int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    scanf("%d", &N);
    if (N == 1) return printf("1\n"), 0;
    if (N <= 3) return printf("NO SOLUTION\n"), 0;
    for (int i = 2; i <= N; i += 2) printf("%d ", i);
    for (int i = 1; i <= N; i += 2) printf("%d ", i);
}