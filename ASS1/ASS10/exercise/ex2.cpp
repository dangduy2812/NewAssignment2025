#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ex2.hpp"
using namespace std;

/* ================================================================
   PHÂN TÍCH:
   Tình huống:
   - Ứng dụng cần đọc playlist dạng text giống .m3u
   - Mỗi dòng có thể:
        + Comment (# hoặc #EXTINF:duration,title)
        + File path (/music/song1.mp3)

   Code mẫu (sai):
        while(getline(fin,line)) { playlist.push_back({line,line,0}); }

   Phân tích:
   - Không kiểm tra #, không parse duration/title
   - Dễ crash khi dòng rỗng hoặc malformed

   Vấn đề:
   - Parser thiếu robust → lỗi khi file có comment, dòng rỗng, title với dấu cách
================================================================ */

/* ================================================================
   FIX:
   Giải pháp:

   Giải pháp 1: Parser robust
       - Lý do: đọc từng dòng, kiểm tra #, parse #EXTINF
       - Nguyên lý: tách duration và title từ #EXTINF, bỏ comment, bỏ dòng rỗng
       - Vì sao chọn: ổn định, xử lý file thực tế tốt

   Giải pháp 2: Sử dụng thư viện playlist parser (optional)
       - Lý do: tự động parse nhiều định dạng
       - Nguyên lý: lib chuẩn hóa cách đọc playlist
       - Vì sao chọn: giảm lỗi, dễ mở rộng
================================================================ */

// ================= PHƯƠNG THỨC SAI ===========================
vector<Song> loadPlaylist_wrong(const char* filepath) {
    cout << "Dang chay phuong thuc sai: parser don gian, khong kiem tra comment\n";
    vector<Song> playlist;
    ifstream fin(filepath);
    if (!fin) { cout << "Khong mo duoc file!\n"; return playlist; }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // Sai: push truc tiep
        playlist.push_back({line, line, 0});
    }
    fin.close();
    cout << "Doc xong (sai)\n";
    return playlist;
}

// ================= PHƯƠNG THỨC ĐÚNG ===========================
vector<Song> loadPlaylist_correct(const char* filepath) {
    cout << "Dang chay phuong thuc dung: parser robust\n";
    vector<Song> playlist;
    ifstream fin(filepath);
    if (!fin) { cout << "Khong mo duoc file!\n"; return playlist; }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        if (line[0] == '#') {
            // #EXTINF:duration,Artist - Title
            if (line.substr(0,7) == "#EXTINF") {
                size_t colon = line.find(':');
                size_t comma = line.find(',');
                if (colon != string::npos && comma != string::npos && comma>colon) {
                    int duration = stoi(line.substr(colon+1, comma-colon-1));
                    string title = line.substr(comma+1);
                    playlist.push_back({title,"",duration});
                }
            }
            continue; // bo comment khac
        }
        // line khong bat dau # -> file path
        playlist.push_back({"", line,0});
    }
    fin.close();
    cout << "Doc xong (dung)\n";
    return playlist;
}

// ================= HIỂN THỊ ===========================
void printPlaylist(const vector<Song>& playlist) {
    for (size_t i=0;i<playlist.size();i++) {
        cout << i+1 << ". ";
        if (!playlist[i].title.empty()) cout << playlist[i].title;
        else cout << playlist[i].filePath;
        if (playlist[i].duration>0) cout << " (" << playlist[i].duration << "s)";
        cout << "\n";
    }
}

// ================= MENU ===========================
void RunEx2() {
    const char* filepath = "playlist.txt";
    int choice;
    do {
        system("cls");
        cout << "===== Exercise 2: Text-Based Playlist Parsing =====\n";
        cout << "1. Chay phuong thuc sai (parser don gian)\n";
        cout << "2. Chay phuong thuc dung (parser robust)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        system("cls");

        vector<Song> playlist;
        switch(choice) {
            case 1:
                playlist = loadPlaylist_wrong(filepath);
                printPlaylist(playlist);
                system("pause");
                break;
            case 2:
                playlist = loadPlaylist_correct(filepath);
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
