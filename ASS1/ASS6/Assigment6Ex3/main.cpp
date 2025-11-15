#include <iostream>
#include <windows.h>   // Cần để dùng HMODULE, LoadLibrary, GetProcAddress, FreeLibrary
using namespace std;

/*

Phân tích 

Scenario:
Ứng dụng có tính năng “3D Surround Sound” chỉ có trên các xe cao cấp.
Thư viện libSurroundDSP.so rất lớn, nếu liên kết động bình thường (-lsurrounddsp),
nó sẽ luôn được nạp khi ứng dụng khởi động -> làm tăng thời gian khởi động và tốn RAM.

Vấn đề:
- Nếu liên kết động (dynamic linking) bình thường tại compile time
  (g++ main.cpp -lsurrounddsp)
  -> Thư viện luôn được nạp khi chương trình khởi động.
  -> Làm **tăng thời gian khởi động** và **tốn RAM**, dù người dùng
    không dùng tính năng này.

Yêu cầu:
1. Khi bật tính năng -> nạp DLL bằng LoadLibrary (tương đương dlopen trên Linux).
2. Lấy địa chỉ hàm initialize_surround_effect bằng GetProcAddress (tương đương dlsym).
3. Gọi hàm thông qua con trỏ hàm.
4. Khi tắt tính năng -> giải phóng thư viện bằng FreeLibrary (tương đương dlclose).
5. Giải thích vì sao plugin model này hiệu quả hơn dynamic linking thông thường.

/* 
Fix (Giải pháp)
“Plugin (Runtime Dynamic Loading)” là một kỹ thuật nạp thư viện động trong lúc chương trình đang chạy, chứ không phải ngay khi biên dịch hay khởi động.

Sử dụng cơ chế runtime dynamic loading (plugin):
- Linux: dùng dlopen() / dlsym() / dlclose()
- Windows: dùng LoadLibrary() / GetProcAddress() / FreeLibrary()

Ưu điểm:
- Giảm thời gian khởi động.
- Giảm RAM vì thư viện chỉ được nạp khi cần.
- Dễ cập nhật module (plugin DLL) riêng lẻ mà không cần build lại app chính.
- Tránh lỗi nếu thư viện không tồn tại (xử lý lỗi runtime).

Nhược điểm:
- Cần kiểm tra lỗi kỹ (thư viện hoặc hàm có thể không tồn tại).
- Gọi hàm qua con trỏ -> mất kiểm tra type safety.
*/


/* Giả lập thư viện plugin DSP */


// Giả lập hàm nằm trong thư viện plugin
extern "C" __declspec(dllexport) void initialize_surround_effect() {
    // extern "C" -> Ngăn C++ name mangling, dễ gọi từ GetProcAddress
    // __declspec(dllexport) -> Xuất hàm ra DLL, để các chương trình khác gọi được
    cout << "[Plugin] Surround Sound Effect initialized successfully!"   // Thông báo plugin đã được khởi tạo
    << endl;
}


// Hàm xử lý tính năng premium (mô phỏng plugin)
// enable = true -> bật, enable = false -> tắt

void enableSurroundFeature(bool enable) {
    static HMODULE hPlugin = NULL; // HMODULE = handle tới DLL, static giữ trạng thái giữa các lần gọi

    if (enable) { // Nếu người dùng bật tính năng
        cout << ">>> User ENABLED Surround Sound Feature" << endl;
        hPlugin = LoadLibrary(TEXT("SurroundDSP.dll"));
        // LoadLibrary -> nạp DLL động (plugin) vào bộ nhớ
        if (!hPlugin) {// Nếu nạp thất bại (file DLL không tồn tại)
            cerr << "Error: Could not load plugin (SurroundDSP.dll not found)." << endl;
            return;// Thoát khỏi hàm, không tiếp tục
        }

        // Lấy địa chỉ hàm từ DLL
        typedef void (*InitFunc)();
        // typedef -> định nghĩa kiểu con trỏ hàm InitFunc trỏ tới hàm void()
        InitFunc initSurround = (InitFunc)GetProcAddress(hPlugin, "initialize_surround_effect");
         // GetProcAddress -> lấy địa chỉ hàm initialize_surround_effect từ DLL

        if (!initSurround) {// Nếu hàm không tìm thấy trong DLL
            cerr << "Error: Function initialize_surround_effect() not found!" << endl;
            FreeLibrary(hPlugin); // Giải phóng DLL khỏi bộ nhớ
            hPlugin = NULL;  // Reset handle
            return;
        }

        // Gọi hàm từ plugin thông qua con trỏ hàm
        initSurround();
    }
    else { // Nếu người dùng tắt tính năng
        cout << ">>> User DISABLED Surround Sound Feature" << endl;
        if (hPlugin) {// Nếu plugin đang được load
            FreeLibrary(hPlugin); // Giải phóng DLL khỏi bộ nhớ
            cout << "[Plugin] Surround Sound library unloaded successfully." << endl; 
            hPlugin = NULL;// Reset handle
        } else {// Nếu chưa load plugin
            cout << "[Info] No plugin was loaded." << endl;
        }
    }
}

int main() {
    cout << "--- MediaPlayer Started ---" << endl;

    enableSurroundFeature(true);   // Bật tính năng cao cấp
    enableSurroundFeature(false);  // Tắt tính năng (giải phóng DLL)

    cout << "--- MediaPlayer End ---" << endl;
    return 0;
}

/*
Kết quả chạy (mô phỏng):
----------------------------------------
--- MediaPlayer Started ---
>>> User ENABLED Surround Sound Feature
[Plugin] Surround Sound Effect initialized successfully!
>>> User DISABLED Surround Sound Feature
[Plugin] Surround Sound library unloaded successfully.
--- MediaPlayer End ---
----------------------------------------

Giải thích:
- LoadLibrary() tương đương dlopen(): chỉ tải DLL khi cần.
- GetProcAddress() tương đương dlsym(): lấy địa chỉ hàm.
- FreeLibrary() tương đương dlclose(): giải phóng tài nguyên.
*/

/* 
So sánh mô hình Plugin vs. Dynamic Linking thông thường:
 Tiêu chí 1: Nạp thư viện
// - Dynamic Linking Thông Thường : Khi chương trình khởi động
// - Plugin Loading (Runtime)     : Khi người dùng kích hoạt
//
// Tiêu chí 2: Dung lượng RAM sử dụng
// - Dynamic Linking Thông Thường : Luôn tốn RAM
// - Plugin Loading (Runtime)     : Tốn RAM khi thật sự cần
//
// Tiêu chí 3: Tốc độ khởi động
// - Dynamic Linking Thông Thường : Chậm hơn
// - Plugin Loading (Runtime)     : Nhanh hơn
//
// Tiêu chí 4: Linh hoạt cập nhật
// - Dynamic Linking Thông Thường : Cần build lại toàn bộ ứng dụng
// - Plugin Loading (Runtime)     : Có thể cập nhật DLL riêng lẻ
//
// Tiêu chí 5: Quản lý lỗi (thiếu DLL)
// - Dynamic Linking Thông Thường : Có thể gây crash khi khởi động
// - Plugin Loading (Runtime)     : Có thể xử lý lỗi runtime an toàn
//
// Tổng kết:
// Dynamic Linking: phù hợp với các thành phần cố định.
// Plugin Loading: linh hoạt, tiết kiệm bộ nhớ và dễ mở rộng ứng dụng.

Trong kịch bản này, mô hình Plugin (Runtime Dynamic Loading) hiệu quả hơn dynamic linking thông thường vì nó chỉ nạp thư viện khi người dùng thực sự cần tính năng cao cấp, giúp giảm thời gian khởi động và tiết kiệm RAM đáng kể.

*/