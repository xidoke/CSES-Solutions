# Review: Increasing Array

## Tổng quan
Bài toán yêu cầu tìm số lần tăng tối thiểu để biến dãy số thành dãy không giảm (non-decreasing).

**Ví dụ:**
- Input: `3 2 5 1 7`
- Output: `5` (tăng 2→3: +1, tăng 1→3: +2, tổng = 3, nhưng thực tế là 5)

**Ý tưởng:** 
- Duyệt từ trái sang phải
- Giữ giá trị lớn nhất đã gặp (`max_val`)
- Nếu số hiện tại < `max_val`, cần tăng lên `max_val`
- Tổng số lần tăng = tổng của `(max_val - a[i])` cho tất cả `a[i] < max_val`

## So sánh Code Master vs Code hiện tại

### Code Master (Phiên bản cũ)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2*10e5+1;
int main() {
    int n; cin >> n;
    int a[MAXN];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < max_val) {
            ans += max_val - a[i];
        }
        else {
            max_val = a[i];
        }
    }
    cout << ans << endl;
    return 0;
}
```

### Code hiện tại (Phiên bản tối ưu)
```cpp
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
```

## Phân tích các Cải thiện

### 1. Tối ưu Bộ nhớ: O(n) → O(1)

#### Code Master
```cpp
int a[MAXN];  // ❌ O(n) space
for (int i = 0; i < n; i++) {
    cin >> a[i];  // Lưu tất cả vào mảng
}
```

**Vấn đề:**
- Cần mảng `a[MAXN]` để lưu tất cả các số
- Lãng phí bộ nhớ: ~800KB cho n = 2*10^5 (nếu dùng int)
- Không cần thiết vì chỉ cần duyệt một lần

#### Code hiện tại
```cpp
ll x, mx, sum;  // ✅ O(1) space
scanf("%lld", &mx);  // Đọc số đầu tiên
for (int i = 1; i < N; i++) {
    scanf("%lld", &x);  // Đọc và xử lý ngay
    // Không cần lưu vào mảng
}
```

**Lợi ích:**
- Chỉ dùng 3 biến: `x`, `mx`, `sum`
- Tiết kiệm bộ nhớ: từ ~800KB xuống ~24 bytes
- Phù hợp với bài toán: chỉ cần duyệt một lần

**So sánh:**
| Tiêu chí | Code Master | Code hiện tại |
|----------|-------------|---------------|
| Space | O(n) ❌ | O(1) ✅ |
| Bộ nhớ (n=2*10^5) | ~800KB | ~24 bytes |
| Cải thiện | - | **33,000 lần** tiết kiệm! |

### 2. Tối ưu Logic: Đọc và xử lý ngay

#### Code Master
```cpp
// Bước 1: Đọc tất cả vào mảng
for (int i = 0; i < n; i++) {
    cin >> a[i];
}

// Bước 2: Duyệt lại mảng để xử lý
for (int i = 1; i < n; i++) {
    if (a[i] < max_val) {
        ans += max_val - a[i];
    }
    else {
        max_val = a[i];
    }
}
```

**Vấn đề:**
- Phải duyệt mảng 2 lần (1 lần đọc, 1 lần xử lý)
- Cache miss: Phải truy cập lại mảng đã đọc

#### Code hiện tại
```cpp
scanf("%lld", &mx);  // Đọc số đầu tiên
for (int i = 1; i < N; i++) {
    scanf("%lld", &x);  // Đọc số tiếp theo
    mx = max(mx, x);    // Xử lý ngay
    sum += mx - x;      // Tính toán ngay
}
```

**Lợi ích:**
- Chỉ duyệt 1 lần: đọc và xử lý cùng lúc
- Cache friendly: Dữ liệu vừa đọc vẫn trong cache
- Code gọn hơn: ít dòng code hơn

**So sánh:**
| Tiêu chí | Code Master | Code hiện tại |
|----------|-------------|---------------|
| Số lần duyệt | 2 lần | 1 lần ✅ |
| Cache efficiency | Thấp | Cao ✅ |
| Độ phức tạp code | Phức tạp hơn | Đơn giản hơn ✅ |

### 3. Tối ưu Logic: Đơn giản hóa điều kiện

#### Code Master
```cpp
if (a[i] < max_val) {
    ans += max_val - a[i];
}
else {
    max_val = a[i];
}
```

#### Code hiện tại
```cpp
mx = max(mx, x);        // Luôn cập nhật max
sum += mx - x;          // Luôn tính (nếu x >= mx thì mx-x = 0)
```

**Phân tích:**
- Code master: Cần kiểm tra `if` mỗi lần
- Code hiện tại: Không cần `if`, dùng `max()` và tính toán trực tiếp
- Khi `x >= mx`: `mx = x`, `sum += x - x = 0` → đúng
- Khi `x < mx`: `mx` giữ nguyên, `sum += mx - x` → đúng

**Lợi ích:**
- Code ngắn gọn hơn: 2 dòng thay vì 5 dòng
- Không có branch prediction overhead
- Dễ đọc và hiểu hơn

### 4. Biến Toàn cục vs Biến Cục bộ

#### Code Master
```cpp
int main() {
    int n;  // Biến cục bộ
    int a[MAXN];
    ll ans = 0;  // Phải khởi tạo thủ công
    // ...
}
```

#### Code hiện tại
```cpp
int N;      // Biến toàn cục
ll x, mx, sum;  // Biến toàn cục
int main() {
    // sum tự động = 0
}
```

#### Lợi ích của Biến Toàn cục trong CP

**1. Tự động khởi tạo = 0**
```cpp
// Biến toàn cục
int sum;        // Tự động = 0
ll total;       // Tự động = 0LL
bool flag;      // Tự động = false

// Biến cục bộ
int main() {
    int sum;    // ❌ Garbage value (undefined behavior)
    ll total;   // ❌ Garbage value
    bool flag;  // ❌ Garbage value
    // Phải khởi tạo thủ công:
    int sum = 0;
    ll total = 0;
    bool flag = false;
}
```

**2. Tiết kiệm code**
```cpp
// Với biến toàn cục
int sum;
int main() {
    // Không cần khởi tạo
    sum += x;
}

// Với biến cục bộ
int main() {
    int sum = 0;  // Phải khởi tạo
    sum += x;
}
```

**3. Dễ debug trong CP**
- Biến toàn cục có thể truy cập từ bất kỳ đâu
- Không cần truyền qua hàm
- Tiện lợi cho competitive programming

**4. Không tốn stack space**
```cpp
// Biến toàn cục: Lưu trong data segment (không giới hạn)
int arr[1000000];  // ✅ OK

// Biến cục bộ: Lưu trong stack (giới hạn ~8MB)
int main() {
    int arr[1000000];  // ❌ Có thể stack overflow
}
```

#### Nhược điểm của Biến Toàn cục

**1. Không an toàn (trong production code)**
```cpp
int sum;  // Bất kỳ hàm nào cũng có thể thay đổi

void bad_function() {
    sum = 999;  // Có thể gây bug
}
```

**2. Khó maintain**
- Khó theo dõi ai đang sử dụng biến
- Dễ gây side effects

**3. Không phù hợp với best practices**
- Trong production code, nên tránh global variables
- Nhưng trong CP, đây là trade-off hợp lý

#### Khi nào dùng Biến Toàn cục trong CP?

**Nên dùng khi:**
- ✅ Cần khởi tạo tự động = 0
- ✅ Cần mảng lớn (tránh stack overflow)
- ✅ Code ngắn gọn (competitive programming)
- ✅ Chỉ có 1 hàm main (không có nhiều hàm)

**Nên dùng Biến cục bộ khi:**
- ✅ Production code
- ✅ Code phức tạp với nhiều hàm
- ✅ Cần encapsulation và safety

#### Kết luận cho bài này

**Code hiện tại dùng biến toàn cục là hợp lý vì:**
- ✅ `sum` tự động = 0 (không cần khởi tạo)
- ✅ Code ngắn gọn hơn
- ✅ Phù hợp với competitive programming style

**Tuy nhiên, có thể cải thiện:**
```cpp
// Cách 1: Giữ nguyên (OK cho CP)
int N;
ll x, mx, sum;

// Cách 2: Khởi tạo rõ ràng (tốt hơn)
int N;
ll x, mx, sum = 0;  // Rõ ràng hơn
```

### 5. Return 0 trong C++11

#### Code Master
```cpp
int main() {
    // ...
    return 0;  // Có return 0
}
```

#### Code hiện tại
```cpp
int main() {
    // ...
    // Không có return 0
}
```

#### Quy tắc C++11 trở đi

**Theo chuẩn C++11 (ISO/IEC 14882:2011):**
- Nếu `main()` không có `return` statement, compiler tự động thêm `return 0;`
- Đây là **implicit return** được chuẩn hóa

**Ví dụ:**
```cpp
// C++11 trở đi
int main() {
    // ...
    // Tự động return 0;
}

// Tương đương với:
int main() {
    // ...
    return 0;
}
```

#### So sánh các phiên bản C++

| Phiên bản | Return 0 | Ghi chú |
|-----------|----------|---------|
| C++98 | Bắt buộc | Phải có `return 0;` |
| C++11 | Tùy chọn | Tự động return 0 nếu không có |
| C++14 | Tùy chọn | Giữ nguyên quy tắc C++11 |
| C++17 | Tùy chọn | Giữ nguyên quy tắc C++11 |

#### Khi nào nên bỏ Return 0?

**Nên bỏ khi:**
- ✅ Dùng C++11 trở đi
- ✅ Code ngắn gọn (competitive programming)
- ✅ Chỉ có 1 đường return (không có early return)

**Nên giữ khi:**
- ✅ Code cũ (C++98)
- ✅ Có nhiều đường return
- ✅ Production code (rõ ràng hơn)
- ✅ Muốn explicit (tường minh)

#### Ví dụ

```cpp
// C++11 - Không cần return 0
int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", n);
    // Tự động return 0
}

// C++11 - Có return 0 (vẫn đúng)
int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", n);
    return 0;  // Explicit, rõ ràng hơn
}

// Có early return - Nên có return
int main() {
    int n;
    scanf("%d", &n);
    if (n < 0) return 1;  // Early return
    printf("%d\n", n);
    return 0;  // Return cuối cùng
}
```

#### Kết luận cho bài này

**Code hiện tại bỏ `return 0;` là hợp lý vì:**
- ✅ C++11 tự động return 0
- ✅ Code ngắn gọn hơn
- ✅ Phù hợp với competitive programming style

**Tuy nhiên, cả hai cách đều đúng:**
```cpp
// Cách 1: Không có return (OK)
int main() {
    // ...
}

// Cách 2: Có return (cũng OK, rõ ràng hơn)
int main() {
    // ...
    return 0;
}
```

### 6. Using vs Typedef

#### Code Master và Code hiện tại
```cpp
using ll = long long;  // Cả hai đều dùng using
```

#### So sánh Using và Typedef

**Typedef (C style):**
```cpp
typedef long long ll;
typedef int arr[100];
typedef void (*func_ptr)(int);
```

**Using (C++11 style):**
```cpp
using ll = long long;
using arr = int[100];
using func_ptr = void(*)(int);
```

#### Ưu điểm của Using

**1. Cú pháp nhất quán với template**
```cpp
// Typedef - Không nhất quán
typedef vector<int> vi;
typedef map<string, int> msi;
// Khác với template syntax

// Using - Nhất quán
using vi = vector<int>;
using msi = map<string, int>;
// Giống với template: template<typename T> using Vec = vector<T>;
```

**2. Hỗ trợ template alias (C++11)**
```cpp
// Typedef - Không hỗ trợ template alias
template<typename T>
typedef vector<T> Vec;  // ❌ Lỗi compile

// Using - Hỗ trợ template alias
template<typename T>
using Vec = vector<T>;  // ✅ OK

Vec<int> v;  // Tương đương vector<int>
```

**3. Dễ đọc hơn**
```cpp
// Typedef - Đọc từ phải sang trái
typedef void (*func)(int);  // "func là pointer đến function nhận int, trả void"

// Using - Đọc từ trái sang phải
using func = void(*)(int);  // "func là alias của void(*)(int)"
```

**4. Hỗ trợ pointer và reference rõ ràng**
```cpp
// Typedef
typedef int* IntPtr;
IntPtr a, b;  // a và b đều là int*

// Using
using IntPtr = int*;
IntPtr a, b;  // a và b đều là int*

// Nhưng với using, có thể làm rõ hơn:
using IntPtr = int*;
IntPtr a;     // int*
int* b;       // int* (rõ ràng hơn)
```

#### Ví dụ thực tế

**Trong Competitive Programming:**
```cpp
// Typedef style (cũ)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

// Using style (mới, khuyến nghị)
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
```

**Với template:**
```cpp
// Typedef - Không thể
// typedef vector<T> Vec;  // ❌ Lỗi

// Using - Có thể
template<typename T>
using Vec = vector<T>;

Vec<int> v1;
Vec<string> v2;
```

#### Khi nào dùng Typedef?

**Nên dùng typedef khi:**
- ⚠️ Code cũ (C++98)
- ⚠️ Cần tương thích với C code
- ⚠️ Team convention yêu cầu

**Nên dùng using khi:**
- ✅ C++11 trở đi (khuyến nghị)
- ✅ Cần template alias
- ✅ Muốn cú pháp nhất quán
- ✅ Competitive programming (modern style)

#### Kết luận

**Code hiện tại dùng `using` là đúng và tốt:**
- ✅ C++11 style (modern)
- ✅ Dễ đọc và nhất quán
- ✅ Hỗ trợ template alias (nếu cần)
- ✅ Phù hợp với competitive programming

**So sánh:**
| Tiêu chí | Typedef | Using |
|----------|---------|-------|
| C++11+ | ✅ | ✅ |
| Template alias | ❌ | ✅ |
| Dễ đọc | Trung bình | Tốt ✅ |
| Nhất quán | Không | Có ✅ |
| Khuyến nghị | C++98 | C++11+ ✅ |

## Tổng hợp các Cải thiện

| Tiêu chí | Code Master | Code hiện tại | Cải thiện |
|----------|-------------|---------------|-----------|
| **Space Complexity** | O(n) | O(1) | ✅ **33,000x** tiết kiệm bộ nhớ |
| **Số lần duyệt** | 2 lần | 1 lần | ✅ **2x** hiệu quả |
| **Cache efficiency** | Thấp | Cao | ✅ Tốt hơn |
| **Code length** | 24 dòng | 16 dòng | ✅ Gọn hơn 33% |
| **Logic complexity** | Có if/else | Không cần | ✅ Đơn giản hơn |
| **Biến toàn cục** | Không | Có | ✅ Tự khởi tạo = 0 |
| **Return 0** | Có | Không | ✅ C++11 tự động |
| **Using vs Typedef** | using | using | ✅ Modern style |

## Code Mẫu Khuyến nghị

### Cách 1: Giữ nguyên style hiện tại (Khuyến nghị cho CP)
```cpp
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
```

**Ưu điểm:**
- ✅ Code ngắn gọn nhất
- ✅ Biến toàn cục tự khởi tạo = 0
- ✅ Không cần return 0 (C++11)
- ✅ Phù hợp với competitive programming

### Cách 2: Explicit style (Khuyến nghị cho production)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N;
    ll x, mx, sum = 0;  // Khởi tạo rõ ràng
    
    scanf("%d", &N);
    scanf("%lld", &mx);
    
    for (int i = 1; i < N; i++) {
        scanf("%lld", &x);
        mx = max(mx, x);
        sum += mx - x;
    }
    
    printf("%lld\n", sum);
    return 0;  // Explicit return
}
```

**Ưu điểm:**
- ✅ Rõ ràng và explicit
- ✅ Dễ maintain
- ✅ Phù hợp với production code

**Kết luận:** Cả hai cách đều đúng. Cách 1 phù hợp với CP, cách 2 phù hợp với production code.

## Lỗi thường gặp

### 1. Dùng mảng không cần thiết
```cpp
int a[MAXN];  // ❌ Không cần
for (int i = 0; i < n; i++) {
    cin >> a[i];
}
// Sau đó mới xử lý
```

**Giải pháp:** Đọc và xử lý ngay trong cùng vòng lặp

### 2. Dùng int thay vì long long
```cpp
int sum = 0;  // ❌ Có thể overflow
// Với n = 2*10^5, mỗi số cần tăng tối đa 10^9
// Tổng có thể lên đến 2*10^14 > 2^31
```

**Giải pháp:** Dùng `long long` cho `sum`

### 3. Không khởi tạo biến
```cpp
ll sum;  // ❌ Không khởi tạo (có thể = garbage value)
```

**Giải pháp:** `ll sum = 0;`

### 4. Logic sai: Không cập nhật max
```cpp
if (x < mx) {
    sum += mx - x;
}
// ❌ Quên cập nhật mx khi x >= mx
```

**Giải pháp:** Luôn cập nhật `mx = max(mx, x);`

## Tổng kết

### Điểm mạnh của Code hiện tại
1. ✅ **O(1) space** - Tối ưu bộ nhớ (tiết kiệm 33,000x)
2. ✅ **1 lần duyệt** - Hiệu quả hơn 2x
3. ✅ **Logic đơn giản** - Không cần if/else
4. ✅ **Biến toàn cục** - Tự khởi tạo = 0, code ngắn gọn
5. ✅ **Không return 0** - C++11 tự động, code ngắn hơn
6. ✅ **Using style** - Modern C++11

### Kết luận
Code hiện tại đã **tối ưu rất tốt** so với code master:
- ✅ Tiết kiệm **33,000x** bộ nhớ (O(n) → O(1))
- ✅ Hiệu quả hơn **2x** về số lần duyệt (2 lần → 1 lần)
- ✅ Code gọn hơn **33%** (24 dòng → 16 dòng)
- ✅ Logic đơn giản hơn (không cần if/else)
- ✅ Tận dụng C++11 features (auto return 0, using)

**Code hiện tại đã rất tốt và phù hợp với competitive programming style!**

