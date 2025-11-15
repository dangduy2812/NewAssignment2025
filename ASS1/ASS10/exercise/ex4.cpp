#include <iostream>
#include <fstream>
#include <cstdio>
#include "ex4.hpp"
using namespace std;

/* ================================================================
   PHÂN TÍCH:
   Tình huống:
   - Khi người dùng sửa playlist, cần ghi file playlist.json
   - Nếu mất điện giữa chừng khi ghi trực tiếp -> file bị hỏng

   Code mẫu (sai):
       ofstream fout("playlist.json");
       fout << json_data;
       fout.close();

   Vấn đề:
   - Ghi trực tiếp file gốc không an toàn
   - Có thể mất dữ liệu nếu ghi dở chừng
================================================================ */

/* ================================================================
   FIX:
   Giải pháp:

   Giải pháp 1: Safe save (atomic save)
       - Lý do: tránh mất dữ liệu khi ghi dở chừng
       - Nguyên lý: ghi file tạm → kiểm tra lỗi → rename sang file gốc
       - Vì sao chọn: rename thường atomic trên filesystem, file gốc còn nguyên nếu lỗi

   Giải pháp 2: Backup + ghi mới
       - Lý do: lưu bản backup trước khi ghi
       - Nguyên lý: copy file gốc → ghi file mới → xóa backup nếu thành công
       - Vì sao chọn: an toàn nhưng cần thêm dung lượng đĩa
================================================================ */

// ================= PHƯƠNG THỨC SAI ===========================
bool savePlaylist_wrong(const vector<Song>& playlist, const char* filepath) {
    cout << "Dang chay phuong thuc sai: ghi truc tiep file goc\n";
    ofstream fout(filepath);
    if (!fout) { cout << "Khong mo duoc file!\n"; return false; }

    for (auto& s : playlist) {
        fout << s.artist << " - " << s.title << "\n";
    }
    fout.close();
    cout << "Ghi xong (sai)\n";
    return true;
}

// ================= PHƯƠNG THỨC ĐÚNG ===========================
bool savePlaylist_correct(const vector<Song>& playlist, const char* filepath) {
    cout << "Dang chay phuong thuc dung: safe save\n";
    string tmpPath = string(filepath) + ".tmp";
    ofstream fout(tmpPath);
    if (!fout) { cout << "Khong mo duoc file tam!\n"; return false; }

    for (auto& s : playlist) {
        fout << s.artist << " - " << s.title << "\n";
    }
    fout.close();

    // Rename atomic
    if (rename(tmpPath.c_str(), filepath) != 0) {
        cout << "Rename khong thanh cong!\n";
        remove(tmpPath.c_str());
        return false;
    }

    cout << "Ghi xong (dung)\n";
    return true;
}

// ================= HIỂN THỊ ===========================
void printPlaylist(const vector<Song>& playlist) {
    for (size_t i = 0; i < playlist.size(); i++) {
        cout << i + 1 << ". " << playlist[i].artist << " - " << playlist[i].title << "\n";
    }
}

// ================= MENU ===========================
void RunEx4() {
    vector<Song> playlist = {
        {"Song A", "Artist 1"},
        {"Song B", "Artist 2"},
        {"Song C", "Artist 3"}
    };
    const char* filepath = "playlist.json";

    int choice;
    do {
        system("cls");
        cout << "===== Exercise 4: Safe Save Playlist =====\n";
        cout << "1. Chay phuong thuc sai (ghi truc tiep file goc)\n";
        cout << "2. Chay phuong thuc dung (safe save)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        system("cls");

        switch(choice) {
            case 1:
                savePlaylist_wrong(playlist, filepath);
                printPlaylist(playlist);
                system("pause");
                break;
            case 2:
                savePlaylist_correct(playlist, filepath);
                printPlaylist(playlist);
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
