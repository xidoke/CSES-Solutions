#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int result = 0;

    for (int i = 1; i < n; i++) {
        int x; cin >> x;
        result ^= i;
        result ^= x;
    }
    result ^= n;
    
    cout << result << endl;
    return 0;
}