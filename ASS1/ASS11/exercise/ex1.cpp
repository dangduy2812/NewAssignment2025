#include "ex1.hpp"
#include <thread>
#include <chrono>

/*
==================================================================
Phân tích: tóm tắt tình huống + code mẫu (nếu có)
------------------------------------------------------------------
Tình huống:
Ứng dụng phát nhạc cần xử lý nhiều loại nguồn âm thanh khác nhau:
- Local File
- Bluetooth
- Internet Radio
Nhưng tất cả đều có các hành động cơ bản: open, read, seek, close.

Vấn đề:
Nếu viết riêng từng lớp mà không có lớp cha trừu tượng,
Player Engine sẽ phải dùng nhiều if/else để kiểm tra loại nguồn,
gây khó bảo trì và mở rộng khi thêm loại nguồn mới.

Code mẫu (rút gọn):
class LocalFileSource { ... }
class BluetoothSource { ... }
=> PlayerEngine phải viết if/else cho từng loại.
==================================================================
*/

/*
==================================================================
Fix: liệt kê giải pháp
------------------------------------------------------------------
Giải pháp 1: Dùng abstract base class (AudioSource)
- Lý do: buộc tất cả lớp con phải triển khai các phương thức cần thiết.
- Nguyên lý hoạt động: khai báo hàm ảo thuần túy (pure virtual),
  để lớp con override theo cơ chế đa hình.
- Vì sao chọn: đảm bảo Player Engine có thể dùng 1 con trỏ AudioSource*
  để thao tác với mọi loại nguồn mà không cần biết loại cụ thể.

Giải pháp 2: Dùng interface (tương tự abstract class)
- Cũng có thể dùng, nhưng trong C++ interface chính là class có
  toàn bộ hàm thuần ảo, nên ta dùng abstract class là đủ.
==================================================================
*/

// Triển khai LocalFileSource
bool LocalFileSource::open(const char* source_path) {
    cout << "[DEBUG] Dang mo file: " << source_path << endl;
    file = fopen(source_path, "rb");
    return file != nullptr;
}

size_t LocalFileSource::read(char* buffer, size_t bytes_to_read) {
    if (!file) return 0;
    cout << "[DEBUG] Dang doc du lieu tu file..." << endl;
    this_thread::sleep_for(chrono::milliseconds(500)); // mô phỏng thời gian đọc
    return fread(buffer, 1, bytes_to_read, file);
}

bool LocalFileSource::seek(long offset) {
    if (!file) return false;
    cout << "[DEBUG] Dang di chuyen con tro file..." << endl;
    return fseek(file, offset, SEEK_SET) == 0;
}

void LocalFileSource::close() {
    if (file) {
        cout << "[DEBUG] Dang dong file..." << endl;
        fclose(file);
        file = nullptr;
    }
}

// Hàm demo minh họa cơ chế đa hình
void runExercise1() {
    cout << "=== Exercise 1: Abstract Class Demo ===" << endl;
    AudioSource* currentSource = new LocalFileSource();

    if (currentSource->open("music_demo.mp3")) {
        char buffer[128];
        currentSource->read(buffer, sizeof(buffer));
        currentSource->seek(0);
        currentSource->close();
    } else {
        cout << "Khong the mo file am thanh." << endl;
    }

    delete currentSource;
    cout << "=== Ket thuc bai 1 ===" << endl;
}
