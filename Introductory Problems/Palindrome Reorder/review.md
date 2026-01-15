# Review: Palindrome Reorder

## Tổng quan bài toán
- Cho một chuỗi chữ hoa `A-Z`, yêu cầu sắp xếp lại để tạo palindrome (nếu không thể thì in `NO SOLUTION`).
- Điều kiện tồn tại: tối đa 1 ký tự có tần suất lẻ.

## Code hiện tại (đã tối ưu, 0.06s → 0.01s trên CSES)
```23:40:Introductory Problems/Palindrome Reorder/main.cpp
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
```

## Kiến thức và kỹ thuật đã áp dụng
- **Đếm tần suất O(n)** với mảng cố định `int cnt[26]` thay vì map; alphabet nhỏ, truy cập chỉ số nhanh.
- **Kiểm tra tính khả thi** bằng số ký tự lẻ `odd > 1` là không thể dựng palindrome.
- **Bit operations**: dùng `cnt[i] & 1` để kiểm tra lẻ và `cnt[i] >> 1` để lấy một nửa, nhanh hơn modulo/chia.
- **Một lần dựng kết quả**: ghép nửa đầu → ký tự lẻ (nếu có) → nửa sau đảo chiều; không dùng string append, chỉ ghi trực tiếp vào buffer `a[]`.
- **Bộ đệm sẵn 1e6 + 1**: tránh cấp phát động, phù hợp kích thước input CSES.
- **I/O nhanh**: `scanf/printf` + tắt sync `iostream` (dù không dùng `cin/cout`, giữ an toàn nếu mở rộng).

## Lý do tối ưu từ 0.06s → 0.01s
- Loại bỏ vòng lặp lồng thừa và chỉ đi qua bảng chữ cái 3 lần cố định (26 phần tử).
- Ghi trực tiếp vào mảng ký tự đã cấp phát, không chuyển đổi sang `string` hay nối chuỗi nhiều lần.
- Sử dụng phép dịch/AND bit thay cho modulo/chia.

## Độ phức tạp
- **Thời gian:** O(n + 26) ≈ O(n).
- **Bộ nhớ:** O(26) cho `cnt` + O(n) cho kết quả trong buffer đầu vào.

## Edge cases đã bao phủ
- Chuỗi chỉ 1 ký tự hoặc toàn bộ một ký tự (palindrome tự nhiên).
- Nhiều hơn 1 ký tự tần suất lẻ ⇒ trả về `NO SOLUTION`.
- Chuỗi độ dài chẵn và lẻ đều xử lý đúng vì phần giữa chỉ thêm khi lẻ.

## Gợi ý kiểm thử nhanh
- `"A"` → `A`
- `"AAA"` → `AAA`
- `"AAB"` → `ABA`
- `"AAABB"` → `ABABA`
- `"ABCD"` → `NO SOLUTION`

