#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2*10e5+1;
int main() {
    int n; cin >> n;
    int flag[MAXN] = {};
    for (int i = 0; i < n-1; i++) {
        int x; cin >> x;
        flag[x] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (flag[i] == 0) {
            cout << i << endl;
            break;
        }
    }
    
    return 0;
}