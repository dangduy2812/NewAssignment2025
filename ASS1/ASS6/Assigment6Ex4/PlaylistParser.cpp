#include <iostream>
using namespace std;

/* =====================
   Technique 1: Dùng namespace ẩn danh
   ===================== */
   /*
Phân tích:
------------------------------------------
 Chúng ta có 1 static library (libPlaylistParser.a) dùng để parse
   các file playlist phức tạp.  
   Trong thư viện này có 1 hàm public:
        void activate_parser(...)
   nhưng cũng có nhiều hàm nội bộ (private) như:
        bool internal_recursive_parse(...)
   => Các hàm nội bộ KHÔNG được export ra ngoài vì người dùng 
   không nên gọi trực tiếp, nếu gọi sai có thể gây lỗi logic.
   
Khi biên dịch một thư viện tĩnh (.lib hoặc .a),
mặc định mọi hàm non-static đều được export (hiện trong bảng symbol).

=> Nếu có hàm nội bộ (vd internal_recursive_parse()),
người khác có thể thấy nó khi chạy lệnh `nm libPlaylistParser.a`
và vô tình gọi trực tiếp.

=> Gây lỗi logic, phá vỡ đóng gói (encapsulation).

Giải pháp:
Dùng namespace ẩn danh (C++ chuẩn)
Dùng __attribute__((visibility("hidden"))) hoặc __declspec(selectany) (compiler-specific)
*/
/*
1) Giải thích “Symbol Visibility” là gì → là khả năng hiển thị 
       các hàm, biến ra bên ngoài file object hoặc library.
2) Thực hành ẩn (hide) hàm nội bộ bằng 2 cách:
       - Technique 1: Dùng namespace ẩn danh (anonymous namespace)
       - Technique 2: Dùng __attribute__((visibility("hidden"))) 
         (chỉ hỗ trợ trên GCC/Linux)
3) Viết lệnh `nm` hoặc `objdump` để kiểm tra symbol trong file .o
       (trên Windows dùng dumpbin thay thế)
       */
namespace {
    bool internal_recursive_parse(const std::string& data) {
        cout << "[internal] parsing: " << data << endl;
        return !data.empty();
    }
}

/* =====================
   Technique 2: static function (ẩn trong translation unit)
   ===================== */
static bool hidden_recursive_parse(const std::string& data) {
    cout << "[hidden] parsing: " << data << endl;
    return data.size() > 2;
}

/* =====================
   Public API function
   ===================== */
void activate_parser(const std::string& fileName) {
    cout << "[public] Activating parser for: " << fileName << endl;

    // Gọi các hàm nội bộ
    if (internal_recursive_parse(fileName))
        cout << "Parsing OK ✅" << endl;
    else
        cout << "Parsing failed ❌" << endl;

    hidden_recursive_parse(fileName);
}
