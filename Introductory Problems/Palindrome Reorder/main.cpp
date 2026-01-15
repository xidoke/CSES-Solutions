#include <bits/stdc++.h>
using namespace std;
using ll = long long;
char a[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    scanf("%s", a);
    int n = strlen(a);
    int cnt[26] = {0};
    int odd = 0;

    for (int i = 0; i < n; i++) cnt[a[i] - 'A']++;
    for (int c : cnt) odd+= c&1;
    if (odd > 1) {
        printf("NO SOLUTION\n");
        return 0;
    }

    int k = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < cnt[i] >> 1; j++) {
            a[k++] = i + 'A';
        }
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i]&1) {
            a[k++] = i + 'A';
        }
    }
    for (int i = 25; i >= 0; i--) {
        for (int j = 0; j < cnt[i] >> 1; j++) {
            a[k++] = i + 'A';
        }
    }
    a[k] = '\0';
    printf("%s\n", a);
    return 0;
}