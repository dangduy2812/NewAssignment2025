#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

/* ================================================================
   PHÂN TÍCH:
   Tình huống: Ứng dụng cần hiển thị thông tin bài hát hiện tại (title, artist, albumArt...).
   Struct SongMetadata chứa dữ liệu rất lớn, đặc biệt là mảng albumArtRawData.

   Vấn đề: Hàm displayMetadata(SongMetadata data) truyền tham trị (pass-by-value),
   nên mỗi lần gọi hàm sẽ tạo ra một bản sao đầy đủ của struct -> tốn thời gian & bộ nhớ.

   Giải thích:
   Khi truyền tham trị, compiler tạo một bản copy đầy đủ của struct trên stack.
   Nếu albumArtRawData có kích thước lớn (vài MB), việc copy này sẽ làm chậm chương trình
   (gây hiện tượng "stutter" khi bài hát mới được chọn).
   ================================================================ */

struct SongMetadata {
    string title;
    string artist;
    string lyrics;
    vector<char> albumArtRawData; // Dữ liệu ảnh album có thể rất lớn
};

//  Hàm gây lỗi hiệu năng (Pass-by-Value)
void displayMetadata_Value(SongMetadata data) {
    cout << "Dang hien thi (Pass-by-Value): " << data.title << endl;
}

/* ================================================================
   FIX:
   Giải pháp: Sử dụng truyền tham chiếu để tránh copy.
   - Truyền tham chiếu (&) giúp không tạo bản sao dữ liệu trên stack.
   - Thêm từ khóa const để đảm bảo dữ liệu gốc không bị sửa trong hàm.
   -> Cú pháp tối ưu: void displayMetadata(const SongMetadata& data)

   Lợi ích của const reference:
   - Tránh copy dữ liệu lớn (tăng hiệu suất)
   - Không cho phép thay đổi dữ liệu gốc (an toàn)
   ================================================================ */

//  Hàm tối ưu hiệu năng (Pass-by-Const-Reference)
void displayMetadata_ConstRef(const SongMetadata& data) {
    cout << "Dang hien thi (Const-Reference): " << data.title << endl;
}

/* ================================================================
   Hàm mô phỏng chạy nhiều bài hát liên tiếp và đo tổng thời gian
   ================================================================ */

void simulateDisplayMultipleSongs(bool useOptimized, int songCount) {
    cout << "\n--- Mo phong hien thi " << songCount << " bai hat ---\n";

    SongMetadata song;
    song.title = "Symphony No.5";
    song.artist = "Beethoven";
    song.lyrics = "Instrumental";
    song.albumArtRawData.resize(20'000'000, 'A'); // 20MB dữ liệu album

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < songCount; ++i) {
        if (useOptimized)
            displayMetadata_ConstRef(song);
        else
            displayMetadata_Value(song);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    cout << "Tong thoi gian xu ly: " << diff.count() << " giay\n";
}

/* ================================================================
   MENU chính
   ================================================================ */

void RunEx1() {
    int choice;
    do {
        cout << "\n===== MENU - Performance Test =====\n";
        cout << "1. Chay ham sai (Pass-by-Value)\n";
        cout << "2. Chay ham dung (Const Reference)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                simulateDisplayMultipleSongs(false, 50); // thử 50 bài
                break;
            case 2:
                simulateDisplayMultipleSongs(true, 50);
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

/* ================================================================
   HÀM MAIN: Tạo vòng lặp mô phỏng nhiều bài hát gọi RunEx1
   ================================================================ */
int main() {
    cout << "=== BAI TAP: Pass-by-Value vs Pass-by-Reference ===\n";
    RunEx1();
    return 0;
}
