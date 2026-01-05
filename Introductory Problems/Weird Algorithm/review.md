# Review: Weird Algorithm

## Tổng quan
Bài toán yêu cầu in ra dãy số theo quy tắc Collatz:
- Nếu n chẵn: n = n / 2
- Nếu n lẻ: n = 3*n + 1
- Dừng khi n = 1

## Lỗi thường gặp

### 1. Tràn kiểu dữ liệu (Integer Overflow)
**Vấn đề:** Khi n lớn, phép tính `3*n + 1` có thể vượt quá giới hạn của `int` (2^31 - 1 ≈ 2.1 tỷ).

**Ví dụ:**
```cpp
int n;  // ❌ SAI - có thể bị tràn
cin >> n;
while (n != 1) {
    if (n % 2 == 1) 
        n = 3*n + 1;  // Có thể tràn nếu n > 715,827,882
    else 
        n /= 2;
}
```

**Giải pháp:** Sử dụng `long long` để tránh tràn:
```cpp
long long n;  // ✅ ĐÚNG
// hoặc
using ll = long long;
ll n;
```

## Tips và cải thiện

### 1. Sử dụng Bit Operations thay vì phép toán thông thường
Bit operations nhanh hơn và code trông chuyên nghiệp hơn:

**Thay vì:**
```cpp
if (n % 2 == 1)  // Kiểm tra số lẻ
    n = 3*n + 1;
else
    n = n / 2;    // Chia cho 2
```

**Nên dùng:**
```cpp
if (n & 1)           // n & 1: kiểm tra bit cuối (1 = lẻ, 0 = chẵn)
    n = 3*n + 1;
else
    n >>= 1;         // n >>= 1: dịch phải 1 bit = chia 2
```

**Lợi ích:**
- **Hiệu suất:** Bit operations nhanh hơn phép chia/modulo
- **Code gọn:** Ngắn gọn và dễ đọc hơn
- **Chuyên nghiệp:** Thể hiện hiểu biết về bit manipulation

### 2. Code mẫu tối ưu
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n; cin >> n;
    
    while (n != 1) {
        cout << n << " ";
        if (n & 1) 
            n = 3*n + 1;
        else 
            n >>= 1;  // Thay vì n /= 2
    }
    cout << n << endl;
    return 0;
}
```

## Ghi chú
- Luôn dùng `long long` cho bài này để tránh overflow
- Bit operations (`&`, `>>`, `<<`) nhanh hơn và là best practice trong competitive programming
- Code hiện tại đã dùng `n & 1` tốt, có thể cải thiện `n /= 2` thành `n >>= 1`

