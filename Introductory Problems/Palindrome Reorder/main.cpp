#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n = s.size();
    int cnt[26] = {0};
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'A']++;
    }
    int odd = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2 == 1) odd++;
    }
    if (odd > 1) printf("NO SOLUTION\n");
    else {
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 0) {
                for (int j = 0; j < cnt[i] / 2; j++) {
                    printf("%c", i + 'A');
                }
            }
        }
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) {
                for (int j = 0; j < cnt[i]; j++) {
                    printf("%c", i + 'A');
                }
            }
        }
        for (int i = 25; i >= 0; i--) {
            if (cnt[i] % 2 == 0) {
                for (int j = 0; j < cnt[i] / 2; j++) {
                    printf("%c", i + 'A');
                }
            }
        }
    }
    return 0;
}