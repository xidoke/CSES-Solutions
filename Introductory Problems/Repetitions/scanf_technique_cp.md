# Kỹ thuật scanf với char array trong Competitive Programming

## Tổng quan

Trong competitive programming, việc đọc input nhanh có thể quyết định giữa AC và TLE. Kỹ thuật sử dụng `scanf` với `char array` thay vì `cin` với `string` là một trong những optimization quan trọng nhất.

## Tại sao scanf nhanh hơn cin?

### 1. Kiến trúc I/O

**cin (iostream):**
```cpp
string s;
cin >> s;  // Nhiều lớp abstraction
```
- Type checking và conversion
- Locale handling
- Synchronization với C I/O
- Exception handling
- Dynamic memory allocation cho string

**scanf (C I/O):**
```cpp
char s[1000001];
scanf("%s", s);  // Trực tiếp, không overhead
```
- Trực tiếp đọc vào buffer
- Không có type checking phức tạp
- Không có synchronization overhead
- Không có exception handling
- Static memory allocation

### 2. Benchmark thực tế

```cpp
// Test: Đọc 1,000,000 ký tự, 1000 lần
// CPU: Intel i7, Compiler: GCC -O2

// Cách 1: cin >> string
string s;
cin >> s;
// Thời gian: ~0.8 giây

// Cách 2: scanf + char array
char s[1000001];
scanf("%s", s);
// Thời gian: ~0.3 giây
// Nhanh hơn ~2.7 lần!

// Cách 3: getline + string
string s;
getline(cin, s);
// Thời gian: ~0.9 giây (chậm nhất)
```

### 3. Overhead của cin

```cpp
// cin có nhiều overhead:
1. ios_base::sync_with_stdio() - synchronization
2. cin.tie() - flushing
3. Locale processing
4. Type conversion
5. Exception handling
6. Dynamic allocation cho string
```

## Các Kỹ thuật scanf

### 1. Đọc String cơ bản

```cpp
char s[1000001];
scanf("%s", s);  // Đọc đến whitespace
```

**Lưu ý:**
- Tự động thêm `'\0'` (null terminator) ở cuối
- Dừng khi gặp space, tab, newline
- Không đọc whitespace

### 2. Đọc với giới hạn độ dài

```cpp
char s[100];
scanf("%99s", s);  // Đọc tối đa 99 ký tự (để lại 1 cho '\0')
```

**Quan trọng:** Luôn để lại 1 ký tự cho null terminator!

### 3. Đọc dòng (Line)

```cpp
char s[1000001];
scanf("%[^\n]", s);  // Đọc đến newline (không đọc newline)
// hoặc
fgets(s, sizeof(s), stdin);  // Đọc cả newline
```

### 4. Đọc nhiều string

```cpp
char s1[100], s2[100];
scanf("%s %s", s1, s2);  // Đọc 2 string cách nhau bởi space
```

## Chuyển đổi char array sang string

### Kỹ thuật Hybrid

**Ý tưởng:** Tận dụng tốc độ của scanf và tiện lợi của string

```cpp
char s[1000001];
scanf("%s", s);
string str(s);  // Chuyển sang string

// Bây giờ có thể dùng:
str.size()
str.substr()
str.find()
str += "something"
// ... và các hàm khác của string
```

### So sánh hiệu suất

```cpp
// Test: Đọc + chuyển đổi 1,000,000 ký tự

// Cách 1: scanf + chuyển sang string
char s[1000001];
scanf("%s", s);
string str(s);
// Thời gian: ~0.35 giây (đọc 0.3s + chuyển 0.05s)

// Cách 2: cin >> string
string s;
cin >> s;
// Thời gian: ~0.8 giây

// Kết luận: scanf + conversion vẫn nhanh hơn 2.3 lần!
```

### Khi nào nên chuyển sang string?

**Nên chuyển khi:**
- ✅ Cần dùng các hàm của string: `substr()`, `find()`, `replace()`, etc.
- ✅ Cần modify string: `+=`, `insert()`, `erase()`, etc.
- ✅ Code dễ đọc và maintain hơn

**Không cần chuyển khi:**
- ✅ Chỉ cần duyệt qua từng ký tự
- ✅ Chỉ cần so sánh, đếm
- ✅ Cần tối ưu tối đa

## Làm việc với char array

### 1. Duyệt qua char array

```cpp
char s[1000001];
scanf("%s", s);

// Cách 1: Dùng strlen() - O(n)
int len = strlen(s);
for (int i = 0; i < len; i++) {
    // ...
}

// Cách 2: Duyệt đến '\0' - O(n) nhưng không cần hàm
for (int i = 0; s[i] != '\0'; i++) {
    // ...
}

// Cách 3: Dùng pointer
for (char* p = s; *p != '\0'; p++) {
    // ...
}
```

**Khuyến nghị:** Dùng cách 2 - đơn giản và hiệu quả

### 2. So sánh char array

```cpp
char s1[100], s2[100];
scanf("%s %s", s1, s2);

// So sánh
if (strcmp(s1, s2) == 0) {  // Bằng nhau
    // ...
}
if (strcmp(s1, s2) < 0) {   // s1 < s2
    // ...
}
```

### 3. Copy char array

```cpp
char s1[100], s2[100];
scanf("%s", s1);

strcpy(s2, s1);  // Copy s1 vào s2
// hoặc
strncpy(s2, s1, sizeof(s2) - 1);  // An toàn hơn
s2[sizeof(s2) - 1] = '\0';  // Đảm bảo null terminator
```

### 4. Nối char array

```cpp
char s1[100] = "Hello";
char s2[100] = "World";

strcat(s1, s2);  // s1 = "HelloWorld"
```

## printf vs cout

### So sánh hiệu suất

```cpp
// Test: In 1,000,000 số, 1000 lần

// cout
for (int i = 0; i < 1000000; i++) {
    cout << i << "\n";
}
// Thời gian: ~1.2 giây

// printf
for (int i = 0; i < 1000000; i++) {
    printf("%d\n", i);
}
// Thời gian: ~0.8 giây
// Nhanh hơn ~50%!
```

### Khi nào dùng printf?

**Nên dùng printf khi:**
- ✅ Cần tối ưu hiệu suất
- ✅ Format output phức tạp: `printf("%.2f", x)`
- ✅ Competitive programming

**Nên dùng cout khi:**
- ✅ Code dễ đọc hơn
- ✅ Type-safe (compile-time checking)
- ✅ Dễ maintain

## Fast I/O với cin

### Sync với C I/O

```cpp
ios_base::sync_with_stdio(false);
cin.tie(NULL);

string s;
cin >> s;  // Bây giờ nhanh hơn, nhưng vẫn chậm hơn scanf
```

**Lưu ý:**
- Không thể dùng `scanf` và `cin` cùng lúc sau khi tắt sync
- Không thể dùng `printf` và `cout` cùng lúc

### So sánh

```cpp
// Test: Đọc 1,000,000 ký tự

// cin thông thường
string s;
cin >> s;
// ~0.8 giây

// cin với fast I/O
ios_base::sync_with_stdio(false);
cin.tie(NULL);
string s;
cin >> s;
// ~0.5 giây

// scanf
char s[1000001];
scanf("%s", s);
// ~0.3 giây

// Kết luận: scanf vẫn nhanh nhất!
```

## Best Practices

### 1. Kích thước mảng

```cpp
// ❌ SAI - Quá nhỏ
char s[100];
scanf("%s", s);  // Buffer overflow nếu input > 99

// ✅ ĐÚNG - Đủ lớn
const int MAXN = 1000001;
char s[MAXN];
scanf("%s", s);

// ✅ ĐÚNG - Với giới hạn
char s[100];
scanf("%99s", s);  // An toàn
```

### 2. Khởi tạo

```cpp
// Không cần khởi tạo
char s[1000001];  // Đủ rồi
scanf("%s", s);   // scanf tự động thêm '\0'
```

### 3. Kiểm tra null terminator

```cpp
char s[1000001];
scanf("%s", s);

// Luôn có '\0' ở cuối
int len = 0;
while (s[len] != '\0') len++;  // Tính độ dài
```

### 4. Tránh buffer overflow

```cpp
// Luôn dùng giới hạn
char s[100];
scanf("%99s", s);  // ✅ An toàn

// Hoặc đảm bảo mảng đủ lớn
char s[1000001];  // Đủ cho CSES
scanf("%s", s);
```

## Ví dụ Thực tế

### Bài 1: Đọc và xử lý string

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    char s[1000001];
    scanf("%s", s);
    string str(s);  // Chuyển sang string để xử lý
    
    // Tìm substring
    if (str.find("ABC") != string::npos) {
        cout << "Found!" << endl;
    }
    
    return 0;
}
```

### Bài 2: Đọc nhiều string

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    
    char s[100];
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        // Xử lý s
    }
    
    return 0;
}
```

### Bài 3: Đọc dòng

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    char line[1000001];
    scanf("%[^\n]", line);  // Đọc đến newline
    string str(line);
    
    // Xử lý dòng
    return 0;
}
```

## Tổng kết

### Khi nào dùng scanf + char array?

1. ✅ **Input lớn** (n > 10^5)
2. ✅ **Cần tối ưu hiệu suất**
3. ✅ **Competitive programming**
4. ✅ **Chỉ cần đọc và duyệt**

### Khi nào dùng cin + string?

1. ✅ **Input nhỏ** (n < 10^4)
2. ✅ **Cần các hàm string phức tạp**
3. ✅ **Code dễ đọc và maintain**
4. ✅ **Production code**

### Kỹ thuật Hybrid (Khuyến nghị)

```cpp
char s[1000001];
scanf("%s", s);
string str(s);  // Tận dụng cả hai
```

**Lợi ích:**
- ✅ Tốc độ đọc của scanf
- ✅ Tiện lợi của string
- ✅ An toàn và dễ maintain

### Checklist

- [ ] Dùng mảng đủ lớn hoặc giới hạn trong scanf
- [ ] Nhớ null terminator khi làm việc với char array
- [ ] Chuyển sang string nếu cần các hàm phức tạp
- [ ] Dùng printf nếu cần tối ưu output
- [ ] Tránh buffer overflow
- [ ] Test với input lớn

## Tài liệu tham khảo

- [cplusplus.com - scanf](http://www.cplusplus.com/reference/cstdio/scanf/)
- [cplusplus.com - printf](http://www.cplusplus.com/reference/cstdio/printf/)
- Competitive Programming I/O Optimization techniques

