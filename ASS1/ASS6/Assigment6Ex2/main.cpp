#include <iostream>
using namespace std;

/* 
Phân tích:

Scenario:
Ứng dụng MediaPlayer liên kết động (dynamic linking) với hai thư viện:
- libUI.so  (giao diện người dùng)
- libAudioEngine.so (xử lý âm thanh)
Cả hai thư viện này "đều phụ thuộc" vào libUtils.so, nhưng:
- libUI.so dùng libUtils.so phiên bản 1.0
- libAudioEngine.so dùng libUtils.so phiên bản 2.0
Hai bản này không tương thích ABI.

=> Đây là tình huống “Diamond Dependency Problem”.

1) Vẽ sơ đồ phụ thuộc (Diamond):

           +-------------------+
           |   MediaPlayer     |
           +-------------------+
             /               \
            /                 \
   +--------------+     +----------------+
   |   libUI.so   |     | libAudioEngine.so |
   +--------------+     +----------------+
          \                  /
           \                /
            +----------------+
            |   libUtils.so  |
            +----------------+
           (v1.0)   (v2.0)  X conflict!


Giải thích:

- Khi MediaPlayer khởi động, dynamic linker (trình liên kết động của hệ điều hành)
  phải chọn một phiên bản duy nhất của libUtils.so để nạp vào bộ nhớ.
- Nhưng vì hai thư viện yêu cầu phiên bản khác nhau, linker không biết
  nên chọn bản nào.
- Thực tế, linker thường nạp phiên bản đầu tiên được tìm thấy (ví dụ v1.0).
  -> Khi libAudioEngine gọi hàm của v2.0 mà chỉ có v1.0 trong bộ nhớ => crash!

=> Kết quả: hành vi không xác định (undefined behavior) — chương trình có thể treo,
   crash, hoặc sai dữ liệu âm thanh / UI.

3) Yêu cầu fix:

Đưa ra các giải pháp kỹ thuật để tránh xung đột giữa libUtils v1.0 và v2.0.
*/

/* 
Fix (Giải pháp kỹ thuật):

Giải pháp 1: Symbol Versioning

- Dùng cơ chế "symbol versioning" của GCC:

1. Cơ chế Hoạt động
Gắn thẻ Phiên bản (Tagging): Khi biên dịch thư viện động (libUtils.so), nhà phát triển sử dụng các công cụ liên kết (Linker) để gán một phiên bản duy nhất cho mỗi ký hiệu (hàm hoặc biến) có trong thư viện.

Ví dụ: Hàm util_A() có thể được gắn thẻ là util_A@UTIL_1.0, và phiên bản đã sửa đổi của nó có thể là util_A@UTIL_2.0.

Lưu trữ Đa phiên bản: Tệp libUtils.so lúc này chứa cả mã của v1.0 và v2.0 cho các hàm không tương thích, mỗi phiên bản được phân biệt bằng thẻ phiên bản.

Liên kết chính xác (Precise Linking):

Khi libUI.so được biên dịch, nó được liên kết với libUtils.so và ghi lại yêu cầu sử dụng util_A@UTIL_1.0.

Khi libAudioEngine.so được biên dịch, nó được liên kết với libUtils.so và ghi lại yêu cầu sử dụng util_A@UTIL_2.0.

Giải quyết khi chạy (Runtime Resolution): Khi MediaPlayer khởi động, Trình tải động (Dynamic Loader) chỉ tải một tệp libUtils.so vào bộ nhớ. Sau đó, nó sử dụng thông tin phiên bản đã ghi lại:

Khi libUI.so gọi util_A(), Loader sẽ trỏ lệnh gọi đến mã của util_A@UTIL_1.0.

Khi libAudioEngine.so gọi util_A(), Loader sẽ trỏ lệnh gọi đến mã của util_A@UTIL_2.0.


- Ví dụ (Linux/GCC):
    void func() __attribute__((symver("func@LIBUTILS_1.0")));

Lưu ý: Cách này chỉ khả dụng trên Linux, không áp dụng trực tiếp trên Windows.
Windows giải quyết vấn đề này chủ yếu thông qua Đổi tên DLL (ví dụ: libUtils_v1.dll và libUtils_v2.dll) hoặc bằng cách sử dụng Version Numbering trong tên tệp DLL để cho phép chúng cùng tồn tại cạnh nhau (Side-by-Side Installation).

Giải pháp 2: Static Linking một bản libUtils

1. Cơ chế Hoạt động
Giả sử chúng ta quyết định liên kết tĩnh libUtils.so v1.0 vào libUI.so:

1. Tạo libUI_new.so
Khi biên dịch lại libUI.so, ta liên kết tĩnh (static link) mã của libUtils v1.0 vào.
Kết quả: tạo ra một file mới gọi là libUI_new.so, trong đó:
Đã chứa toàn bộ mã của libUtils v1.0
Không cần tải thêm libUtils.so bên ngoài nữa.

Nói cách khác:
libUI_new.so bây giờ tự cung cấp phần tiện ích của nó — không còn phụ thuộc vào libUtils.so.
2. Khi MediaPlayer khởi động
Trình nạp động (dynamic loader) của hệ thống sẽ:
Tải libUI_new.so → bên trong đã có sẵn mã của libUtils v1.0.
Tải libAudioEngine.so, cái này vẫn cần libUtils.so v2.0.

3. Kết quả đạt được
Trong bộ nhớ:
libUtils v1.0 nằm bên trong libUI_new.so (dạng tĩnh, không bị chia sẻ).
libUtils v2.0 là thư viện động duy nhất được nạp riêng.
Do đó:
Hệ thống chỉ phải tải động một bản libUtils (v2.0).
Không còn xung đột ABI, vì hai phiên bản libUtils không “đụng” vào nhau trong vùng liên kết động.

Giải pháp 3: Refactor 
 Tái cấu trúc mã nguồn để loại bỏ tận gốc vấn đề xung đột giữa các phiên bản thư viện.
- Chuẩn hóa để tất cả các module (UI, Audio, MediaPlayer)
  dùng cùng một phiên bản libUtils (ví dụ v2.0).
- Đây là cách mạnh mẽ nhất, ít rủi ro, dễ bảo trì về lâu dài.
*/

/* 
Code mô phỏng (Windows)
Mô phỏng ý tưởng rằng:
- UI dùng "Utils v1"
- AudioEngine dùng "Utils v2"
- Khi chạy, nếu cùng tồn tại -> dễ xảy ra xung đột.

Ta sẽ mô phỏng bằng class, không cần thật thư viện.
*/

class LibUtils_v1 {
public:
    static void log() {
        cout << "[libUtils v1.0] Logging basic info" << endl;
    }
};

class LibUtils_v2 {
public:
    static void log() {
        cout << "[libUtils v2.0] Logging advanced info + timestamp" << endl;
    }
};

class LibUI {
public:
    void draw() {
        cout << "UI: Drawing interface..." << endl;
        LibUtils_v1::log(); // Gọi hàm từ v1
    }
};

class LibAudioEngine {
public:
    void processAudio() {
        cout << "Audio: Processing sound..." << endl;
        LibUtils_v2::log(); // Gọi hàm từ v2
    }
};

int main() {
    cout << "--- Bắt đầu mô phỏng Diamond Dependency ---" << endl;

    LibUI ui;
    ui.draw();

    LibAudioEngine audio;
    audio.processAudio();

    cout << "--- Kết thúc mô phỏng ---" << endl;
    return 0;
}

/*
Kết quả chạy:
--------------------------------------------
--- Bắt đầu mô phỏng Diamond Dependency ---
UI: Drawing interface...
[libUtils v1.0] Logging basic info
Audio: Processing sound...
[libUtils v2.0] Logging advanced info + timestamp
--- Kết thúc mô phỏng ---
--------------------------------------------

Giải thích:
- Mỗi thư viện gọi đúng phiên bản của libUtils tương ứng.
- Nếu trên thực tế dynamic linker không thể phân tách -> lỗi xung đột xảy ra.
*/
