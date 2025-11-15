#include <iostream>
#include <fstream>
#include <cstring>
#include "ex1.hpp"
using namespace std;

/* ================================================================
   PHÂN TÍCH:
   Tình huống:
   - Lưu/đọc cấu hình người dùng (volume, shuffle, last track ID, EQ presets)
   - Code mẫu (sai) ghi trực tiếp struct:
        ofstream fout("settings.bin", ios::binary);
        fout.write(reinterpret_cast<const char*>(&settings), sizeof(UserSettings));

   Phân tích tình huống:
   - Struct padding: compiler có thể thêm byte rỗng để align
   - Endianness: CPU khác nhau đọc byte khác nhau

   Vấn đề:
   - Ghi/đọc trực tiếp struct không portable
   - Có thể dẫn tới lỗi khi đọc trên máy khác
================================================================ */

/* ================================================================
   FIX:
   Giải pháp:

   Giải pháp 1: Serialize từng field
       - Lý do: Tránh struct padding và đảm bảo thứ tự byte cố định
       - Nguyên lý: Ghi/đọc từng biến riêng lẻ vào file nhị phân
       - Vì sao chọn: Phù hợp với nhiều kiến trúc, portable, nhanh

   Giải pháp 2: Sử dụng thư viện serialization (ví dụ protobuf, cereal)
       - Lý do: Quản lý tự động padding, endian, versioning
       - Nguyên lý: Thư viện chuẩn hóa cách ghi/đọc dữ liệu
       - Vì sao chọn: Dễ mở rộng, giảm lỗi, hỗ trợ cross-platform
================================================================ */

// ================= PHƯƠNG THỨC SAI ===========================
bool saveSettings_wrong(const UserSettings& settings, const char* filepath) {
    cout << "Dang chay phuong thuc sai: ghi truc tiep struct\n";
    ofstream fout(filepath, ios::binary);
    if (!fout) { cout << "Khong mo duoc file!\n"; return false; }
    fout.write(reinterpret_cast<const char*>(&settings), sizeof(UserSettings));
    fout.close();
    cout << "Ghi xong (sai)\n";
    return true;
}

bool loadSettings_wrong(UserSettings& settings, const char* filepath) {
    cout << "Dang chay phuong thuc sai: doc truc tiep struct\n";
    ifstream fin(filepath, ios::binary);
    if (!fin) { cout << "Khong mo duoc file!\n"; return false; }
    fin.read(reinterpret_cast<char*>(&settings), sizeof(UserSettings));
    fin.close();
    cout << "Doc xong (sai)\n";
    return true;
}

// ================= PHƯƠNG THỨC ĐÚNG ===========================
bool saveSettings_correct(const UserSettings& settings, const char* filepath) {
    cout << "Dang chay phuong thuc dung: serialize tung field\n";
    ofstream fout(filepath, ios::binary);
    if (!fout) { cout << "Khong mo duoc file!\n"; return false; }

    fout.write(reinterpret_cast<const char*>(&settings.last_volume), sizeof(settings.last_volume));
    fout.write(reinterpret_cast<const char*>(&settings.shuffle_mode_enabled), sizeof(settings.shuffle_mode_enabled));
    fout.write(reinterpret_cast<const char*>(&settings.last_played_track_id), sizeof(settings.last_played_track_id));
    fout.write(reinterpret_cast<const char*>(settings.eq_presets), sizeof(settings.eq_presets));

    fout.close();
    cout << "Ghi xong (dung)\n";
    return true;
}

bool loadSettings_correct(UserSettings& settings, const char* filepath) {
    cout << "Dang chay phuong thuc dung: doc tung field\n";
    ifstream fin(filepath, ios::binary);
    if (!fin) { cout << "Khong mo duoc file!\n"; return false; }

    fin.read(reinterpret_cast<char*>(&settings.last_volume), sizeof(settings.last_volume));
    fin.read(reinterpret_cast<char*>(&settings.shuffle_mode_enabled), sizeof(settings.shuffle_mode_enabled));
    fin.read(reinterpret_cast<char*>(&settings.last_played_track_id), sizeof(settings.last_played_track_id));
    fin.read(reinterpret_cast<char*>(settings.eq_presets), sizeof(settings.eq_presets));

    fin.close();
    cout << "Doc xong (dung)\n";
    return true;
}

// ================= HIỂN THỊ ===========================
void printSettings(const UserSettings& s) {
    cout << "Last volume: " << s.last_volume << "\n";
    cout << "Shuffle: " << s.shuffle_mode_enabled << "\n";
    cout << "Last track ID: " << s.last_played_track_id << "\n";
    cout << "EQ presets: ";
    for (int i = 0; i < EQ_BANDS; i++) cout << s.eq_presets[i] << " ";
    cout << "\n";
}

// ================= MENU ===========================
void RunEx1() {
    const char* filepath = "settings.bin";
    UserSettings s1 = {50, true, 123456789, {0.5f,0.6f,0.7f,0.8f,0.9f,1.0f,1.1f,1.2f,1.3f,1.4f}};
    UserSettings s2;

    int choice;
    do {
        system("cls");
        cout << "===== Exercise 1: Binary Configuration Data =====\n";
        cout << "1. Chay phuong thuc sai (ghi/doc truc tiep struct)\n";
        cout << "2. Chay phuong thuc dung (serialize tung field)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                saveSettings_wrong(s1, filepath);
                loadSettings_wrong(s2, filepath);
                printSettings(s2);
                system("pause");
                break;
            case 2:
                saveSettings_correct(s1, filepath);
                loadSettings_correct(s2, filepath);
                printSettings(s2);
                system("pause");
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                system("pause");
        }
    } while (choice != 0);
}
