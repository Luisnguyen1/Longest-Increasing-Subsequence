# Hướng dẫn thuật toán tìm dãy con tăng dài nhất (LIS)

Tài liệu này giải thích chi tiết về thuật toán tìm dãy con tăng dài nhất (Longest Increasing Subsequence - LIS) với độ phức tạp O(n log n) được cài đặt trong file `LIS.cpp`.

## Tổng quan thuật toán

Thuật toán này dựa trên ý tưởng của Patience Sort (Sắp xếp kiên nhẫn), sử dụng các "chồng bài" để xác định độ dài và phần tử của dãy con tăng dài nhất.

### Sơ đồ tổng quan của thuật toán

```mermaid
flowchart TD
    A[Khởi tạo: piles, prev, pos] --> B[Duyệt qua từng phần tử]
    B --> C{Phần tử lớn hơn\ntất cả trong piles?}
    C -- Có --> D[Thêm phần tử vào cuối piles\nCập nhật prev và pos]
    C -- Không --> E[Tìm vị trí thích hợp bằng binary search\nThay thế phần tử\nCập nhật prev và pos]
    D --> F{Còn phần tử?}
    E --> F
    F -- Có --> B
    F -- Không --> G[Dựng lại LIS từ piles và prev]
    G --> H[Đảo ngược LIS]
    H --> I[Trả về kết quả]
```

## Các cấu trúc dữ liệu chính

Thuật toán sử dụng ba cấu trúc dữ liệu chính để lưu trữ thông tin:

1. **piles**: Lưu chỉ số của phần tử nhỏ nhất kết thúc một dãy con tăng có độ dài i+1
2. **prev**: Lưu chỉ số của phần tử trước đó trong LIS kết thúc tại vị trí i
3. **pos**: Lưu vị trí trong LIS mà phần tử tại chỉ số i thuộc về

## Chi tiết quá trình xử lý mỗi phần tử

```mermaid
flowchart TD
    A["Phần tử hiện tại: nums[i]"] --> B["Tìm kiếm nhị phân trong piles"]
    B --> C{"Kết quả tìm kiếm?"}
    C -- "piles.end()" --> D["Mở rộng LIS"]
    C -- "Vị trí khác" --> E["Thay thế phần tử"]
    
    D --> D1["prev[i] = piles.back()"]
    D1 --> D2["piles.push_back(i)"]
    D2 --> D3["pos[i] = piles.size() - 1"]
    
    E --> E1{"it != piles.begin()?"}
    E1 -- "Có" --> E2["prev[i] = piles[it-piles.begin()-1]"]
    E1 -- "Không" --> E3["prev[i] = -1"]
    E2 --> E4["*it = i"]
    E3 --> E4
    E4 --> E5["pos[i] = it-piles.begin()"]
```

### Minh họa tìm kiếm nhị phân

```mermaid
flowchart LR
    subgraph "Binary Search"
        direction TB
        B1["lower_bound"] --> B2{"So sánh nums[piles[mid]] với current"}
        B2 --> B3["Điều chỉnh left hoặc right"]
        B3 --> B2
    end
    
    subgraph "Kết quả"
        direction TB
        R1["Tìm thấy vị trí"] --> R2{"vị trí == piles.end()?"}
        R2 -- "Có" --> R3["Thêm mới"]
        R2 -- "Không" --> R4["Thay thế"]
    end
    
    B1 --> R1
```

## Quá trình dựng lại LIS

```mermaid
flowchart TD
    A["Khởi tạo lis rỗng"] --> B{"piles rỗng?"}
    B -- "Có" --> C["Trả về lis rỗng"]
    B -- "Không" --> D["idx = piles.back()"]
    D --> E["Thêm idx vào lis"]
    E --> F["idx = prev[idx]"]
    F --> G{"idx == -1?"}
    G -- "Có" --> H["Đảo ngược lis"]
    G -- "Không" --> E
    H --> I["Trả về lis"]
```

## Ví dụ minh họa

Với dãy đầu vào: `1, 4, 10, 9, 8, 17, 11, 7, 12, 6`

```mermaid
sequenceDiagram
    participant Input as Dãy đầu vào
    participant Piles as Mảng piles
    participant Prev as Mảng prev
    participant Result as Kết quả LIS
    
    Note over Input: 1, 4, 10, 9, 8, 17, 11, 7, 12, 6
    
    Input->>Piles: Xử lý 1
    Note over Piles: [0]
    Note over Prev: prev[0] = -1
    
    Input->>Piles: Xử lý 4
    Note over Piles: [0, 1]
    Note over Prev: prev[1] = 0
    
    Input->>Piles: Xử lý 10
    Note over Piles: [0, 1, 2]
    Note over Prev: prev[2] = 1
    
    Input->>Piles: Xử lý 9
    Note over Piles: [0, 1, 3]
    Note over Prev: prev[3] = 1
    
    Input->>Piles: Xử lý 8
    Note over Piles: [0, 1, 4]
    Note over Prev: prev[4] = 1
    
    Input->>Piles: Xử lý 17
    Note over Piles: [0, 1, 4, 5]
    Note over Prev: prev[5] = 4
    
    Input->>Piles: Xử lý 11
    Note over Piles: [0, 1, 4, 6]
    Note over Prev: prev[6] = 4
    
    Input->>Piles: Xử lý 7
    Note over Piles: [0, 1, 7, 6]
    Note over Prev: prev[7] = 1
    
    Input->>Piles: Xử lý 12
    Note over Piles: [0, 1, 7, 6, 8]
    Note over Prev: prev[8] = 6
    
    Input->>Piles: Xử lý 6
    Note over Piles: [0, 1, 9, 6, 8]
    Note over Prev: prev[9] = 1
    
    Piles->>Result: Dựng LIS từ prev
    Note over Result: Chỉ số: 0, 1, 5, 6, 8
    Note over Result: Giá trị: 1, 4, 17, 11, 12
    Note over Result: Vị trí (1-indexed): 1, 2, 6, 7, 9
```

## Phân tích độ phức tạp

- **Thời gian**: O(n log n)
  - Vòng lặp chính: O(n)
  - Tìm kiếm nhị phân trong mỗi bước: O(log n)
  
- **Không gian**: O(n)
  - Mảng piles, prev, pos: mỗi mảng có kích thước O(n)

## Lưu ý quan trọng

Kết quả cuối cùng không nhất thiết phải chứa các phần tử cuối cùng của mỗi chồng. Điều này vì:

1. Khi dựng lại LIS, ta bắt đầu từ phần tử cuối cùng trong `piles` và sử dụng mảng `prev` để truy ngược lại.
2. Một phần tử có thể được thay thế trong một chồng, nhưng vẫn là một phần của LIS thực tế khi dựng lại từ mảng `prev`.
