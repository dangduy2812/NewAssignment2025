#include "ex4.hpp"
#include <thread>
#include <chrono>

/*
==================================================================
Phân tích: tóm tắt tình huống + code mẫu (nếu có)
------------------------------------------------------------------
Tình huống:
Ứng dụng cần import nhiều loại playlist (.txt, .xml).
Các bước xử lý luôn giống nhau: Open → Parse → Validate → Add → Close.

Vấn đề:
Nếu viết riêng cho từng loại file sẽ bị lặp lại nhiều đoạn code.

Code mẫu ban đầu:
parseTxt(), parseXml() → mỗi hàm tự xử lý toàn bộ → trùng lặp logic.
==================================================================
*/

/*
==================================================================
Fix: liệt kê giải pháp
------------------------------------------------------------------
Giải pháp 1: Dùng Template Method Pattern
- Lý do: Gom các bước chung vào lớp cha, cho phép lớp con tùy chỉnh bước riêng.
- Nguyên lý hoạt động: Lớp cha định nghĩa khung (template method),
  lớp con override các bước thay đổi (parse, validate).
- Vì sao chọn: Giảm trùng lặp, dễ mở rộng, đảm bảo trình tự xử lý chuẩn.

Giải pháp 2: Kết hợp thêm Strategy Pattern (nếu cần linh hoạt runtime)
==================================================================
*/

// ===================== TRIỂN KHAI ===============================

bool PlaylistImporter::open(const string& path) {
    cout << "[DEBUG] Dang mo file: " << path << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    return true;
}

void PlaylistImporter::addToLibrary() {
    cout << "[DEBUG] Dang them bai hat vao thu vien..." << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
}

void PlaylistImporter::close() {
    cout << "[DEBUG] Dong file hoan tat." << endl;
}

void PlaylistImporter::importFromFile(const string& path) {
    cout << "[DEBUG] Bat dau quy trinh import playlist\n";
    if (!open(path)) {
        cout << "[ERROR] Khong mo duoc file.\n";
        return;
    }
    if (!parseContents()) {
        cout << "[ERROR] Loi khi phan tich noi dung file.\n";
        close();
        return;
    }
    if (!validateSongs()) {
        cout << "[ERROR] File khong hop le.\n";
        close();
        return;
    }
    addToLibrary();
    close();
    cout << "[INFO] Import thanh cong!\n";
}

// ================== TXT IMPORTER =====================

bool TxtPlaylistImporter::parseContents() {
    cout << "[DEBUG] Dang parse file .txt..." << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "[DEBUG] Tim thay 5 bai hat trong file txt.\n";
    return true;
}

bool TxtPlaylistImporter::validateSongs() {
    cout << "[DEBUG] Dang kiem tra tinh hop le cua danh sach .txt..." << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    return true;
}

// ================== XML IMPORTER =====================

bool XmlPlaylistImporter::parseContents() {
    cout << "[DEBUG] Dang parse file .xml..." << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "[DEBUG] Doc duoc 3 bai hat co metadata.\n";
    return true;
}

bool XmlPlaylistImporter::validateSongs() {
    cout << "[DEBUG] Dang kiem tra tinh hop le cua danh sach .xml..." << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    return true;
}

// ================= DEMO CHÍNH ========================

void runExercise4() {
    cout << "=== Exercise 4: Template Method Pattern ===\n";
    int choice;
    do {
        cout << "\n1. Import playlist .txt\n";
        cout << "2. Import playlist .xml\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            cout << "[DEBUG] Dang su dung TxtPlaylistImporter\n";
            TxtPlaylistImporter txt;
            txt.importFromFile("playlist.txt");
            break;
        }
        case 2: {
            cout << "[DEBUG] Dang su dung XmlPlaylistImporter\n";
            XmlPlaylistImporter xml;
            xml.importFromFile("playlist.xml");
            break;
        }
        case 0:
            cout << "Thoat bai 4\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }

        if (choice != 0) {
            cout << "\nNhan phim bat ky de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
        }

    } while (choice != 0);

    cout << "=== Ket thuc bai 4 ===\n";
}
