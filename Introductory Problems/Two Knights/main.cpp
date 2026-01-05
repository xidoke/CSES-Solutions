#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int main() {
    int n; cin >> n;

    for (int k = 1; k <= n; k++) {
        ull attacks = 4*(k-1)*(k-2);
        ull total = 1ull*k*k*(k*k-1)/2;
        cout << total - attacks << endl;
    }

    return 0;
}