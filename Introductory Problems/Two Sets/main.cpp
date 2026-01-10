#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    if(N%4 == 1 || N%4 == 2)  return printf("NO\n"), 0;

    if (N % 4 == 0) {
        printf("YES\n");
        printf("%d\n", N/2);
        for (int i = 1; i <= N/2; i += 2) {
            printf("%d %d ", i, N-i+1);
        }
        printf("\n");
        printf("%d\n", N/2);
        for (int i = 2; i <= N/2; i += 2) {
            printf("%d %d ", i, N-i+1);
        }
        printf("\n");
    }
 
    if (N % 4 == 3) {
        printf("YES\n");
        printf("%d\n", N/2);
        for (int i = 2; i <= N/2; i += 2) {
            printf("%d %d ", i, N-i);
        }
        printf("%d\n%d\n", N, N/2+1);
        for (int i = 1; i <= N/2; i += 2) {
            printf("%d %d ", i, N-i);
        }
        printf("\n");
    }
}