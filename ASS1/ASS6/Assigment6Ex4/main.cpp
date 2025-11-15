#include <iostream>
using namespace std;

/* 
PHÂN TÍCH
 Yêu cầu đề bài:
- Ta có thư viện tĩnh `libPlaylistParser.a`, chứa hàm public:
    void activate_parser(...)
- Bên trong có hàm nội bộ (internal helper):
    bool internal_recursive_parse(...)
- Vấn đề: Khi build thư viện, tất cả hàm không có từ khóa `static` 
  đều bị export (hiển thị) trong symbol table.
  => Lập trình viên khác có thể thấy và gọi nhầm hàm nội bộ này.

Câu hỏi:
"Symbol Visibility" là gì?  
   - Là khả năng hiển thị (export) các hàm hoặc biến trong file nhị phân (binary) hoặc thư viện.  
   - Nếu symbol "visible", nó có thể bị truy cập từ ngoài module (file hoặc library khác).  
   - Nếu "hidden", nó chỉ dùng nội bộ — giúp ẩn chi tiết cài đặt và tránh xung đột tên.  

    Kiểm soát visibility rất quan trọng:
   - Giúp đảm bảo encapsulation (đóng gói).
   - Tăng bảo mật, tránh gọi nhầm.
   - Giảm kích thước bảng symbol và tăng tốc linking.
   - Giảm xung đột tên khi link nhiều thư viện cùng có tên hàm giống nhau.


Cách ẩn symbol nội bộ (`internal_recursive_parse`)  

    Cách 1: Dùng anonymous namespace (chuẩn C++)  
       -> Mọi hàm/biến trong anonymous namespace chỉ có hiệu lực nội bộ trong file đó.

    Cách 2: Dùng compiler attribute (Linux: `__attribute__((visibility("hidden")))`)  
       -> Báo cho trình biên dịch không export symbol ra ngoài.
        Ghi chú: Trên Windows, thay bằng `__declspec(dllexport)` hoặc `__declspec(dllexport)` tùy mục đích.
       Ở đây ta mô phỏng tương đương bằng cách dùng `static`.

 Xác minh bằng công cụ:
   - Trên Linux:
        nm libPlaylistParser.a
     Sau khi ẩn symbol, ta mong thấy:
        "T internal_recursive_parse" -> chuyển thành "t internal_recursive_parse"
     Nghĩa là: symbol từ "global (T)" -> "local (t)" → không export ra ngoài.

   - Trên Windows:
        dumpbin /symbols libPlaylistParser.lib
     Nếu dùng `static` hoặc namespace, symbol internal sẽ không hiển thị.


 Giải pháp (Fix):

*/
// 1 Technique 1: Dùng anonymous namespace (chuẩn C++)
namespace {
    bool internal_recursive_parse(const string& filename) {
        // Hàm nội bộ, không xuất ra global symbol
        cout << "[internal] parsing file: " << filename << endl;
        return true;
    }
}
// Public API (exported)

void activate_parser(const string& filename) {
    cout << "[public] activate_parser called.\n";
      // Gọi hàm nội bộ bên trong file, vẫn hoạt động bình thường
    internal_recursive_parse(filename);
}

/* ==========================================================
 Technique 2 (Compiler-specific):
   - Linux: bool __attribute__((visibility("hidden"))) internal_recursive_parse(...)
   - Windows: dùng static hoặc để trong anonymous namespace (đã dùng ở trên)

   __attribute__((visibility("hidden"))) 
bool internal_recursive_parse(const char* data, int depth) {
    std::cout << "[internal] Parsing depth " << depth << std::endl;
    return depth >= 0;
}

void activate_parser() {
    const char* sample = "playlist data";
    internal_recursive_parse(sample, 0); // gọi nội bộ
}
 */
/*
static trong C++/Windows → file scope (chỉ visible trong file .cpp này).
Tương tự như anonymous namespace.
Khi biên dịch thành DLL hoặc lib, symbol không xuất ra ngoài -> không thể gọi từ file khác.
*/ 
static bool internal_recursive_parse_tech2(const string& filename) {
    cout << "[internal] parsing file: " << filename << endl;
    return true;
}
void activate_parser_tech2(const string& filename) {
    cout << "[public] activate_parser called.\n";
    internal_recursive_parse(filename);
}

int main() {
    cout << "=== Playlist Parser Test ===\n";
    activate_parser("my_playlist.m3u");
    cout << "\n=== Test Static Library Symbol Visibility ===\n";
    activate_parser_tech2("playlist.m3u");

    // Giả lập: nếu người khác cố gọi hàm nội bộ -> lỗi biên dịch
    // internal_recursive_parse("abc"); // <-- Không thấy symbol này
    return 0;
}

/*
Phân tích:
- Hàm internal_recursive_parse() bị ẩn, không export symbol ra file .lib.
- Nếu người dùng bên ngoài cố gọi -> compiler báo lỗi "undefined reference".
- Điều này giúp thư viện bảo toàn đóng gói và an toàn hơn.
*/
/*
mingw32-make
main.exe

kết quả chạy chương trình:
=== Playlist Parser Test ===
[public] Activating parser for: my_playlist.m3u
[internal] parsing: my_playlist.m3u

=== Test Static Library Symbol Visibility ===
[public] activate_parser called.
[internal] parsing file: playlist.m3u

Parsing OK 
Nếu cố gọi internal_recursive_parse() từ main.cpp,
trình biên dịch sẽ báo lỗi:
undefined reference to `internal_recursive_parse(...)'

*/