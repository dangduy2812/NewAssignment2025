#include <iostream>
#include <fstream>
#include "ex3.hpp"
using namespace std;

/* ================================================================
   PHÂN TÍCH:
   Tình huống:
   - Ứng dụng cần phát file âm thanh lớn (100MB WAV)
   - File quá lớn để load toàn bộ vào RAM

   Code mẫu (sai):
       ifstream fin(filepath, ios::binary);
       fin.read(buffer, filesize);

   Vấn đề:
   - Load toàn bộ file → tốn RAM, có thể crash trên hệ thống nhúng
================================================================ */

/* ================================================================
   FIX:
   Giải pháp:

   Giải pháp 1: Đọc theo chunks
       - Lý do: Giảm sử dụng RAM, xử lý streaming
       - Nguyên lý: đọc từng BUFFER_SIZE byte vào buffer, xử lý, lặp lại
       - Vì sao chọn: tiết kiệm bộ nhớ, phù hợp hệ thống nhúng

   Giải pháp 2: Memory-mapped file (optional)
       - Lý do: OS quản lý paging, đọc file như mảng
       - Nguyên lý: map file vào bộ nhớ, truy xuất từng phần
       - Vì sao chọn: hiệu năng cao, không cần load toàn bộ file
================================================================ */

// ================= PHƯƠNG THỨC SAI ===========================
void playAudioFile_wrong(const char* filepath) {
    cout << "Dang chay phuong thuc sai: doc toan bo file cung luc\n";
    ifstream fin(filepath, ios::binary | ios::ate);
    if (!fin) { cout << "Khong mo duoc file!\n"; return; }

    streamsize size = fin.tellg();
    fin.seekg(0, ios::beg);

    char* buffer = new char[size];
    fin.read(buffer, size);
    fin.close();

    cout << "Da doc file " << size << " bytes (sai)\n";

    delete[] buffer;
}

// ================= PHƯƠNG THỨC ĐÚNG ===========================
void playAudioFile_correct(const char* filepath) {
    cout << "Dang chay phuong thuc dung: doc file theo chunks\n";
    ifstream fin(filepath, ios::binary);
    if (!fin) { cout << "Khong mo duoc file!\n"; return; }

    // Skip header 44 bytes (WAV)
    fin.seekg(44, ios::beg);

    char buffer[BUFFER_SIZE];
    size_t totalRead = 0;

    while (!fin.eof()) {
        fin.read(buffer, BUFFER_SIZE);
        streamsize bytesRead = fin.gcount();
        if (bytesRead <= 0) break;

        // Simulate processing audio chunk
        totalRead += bytesRead;
    }

    fin.close();
    cout << "Da doc file " << totalRead << " bytes theo chunks (dung)\n";
}

// ================= MENU ===========================
void RunEx3() {
    const char* filepath = "test.wav"; // can chinh theo file co san
    int choice;
    do {
        system("cls");
        cout << "===== Exercise 3: Chunk Audio File =====\n";
        cout << "1. Chay phuong thuc sai (doc toan bo file)\n";
        cout << "2. Chay phuong thuc dung (doc theo chunks)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        system("cls");

        switch(choice) {
            case 1:
                playAudioFile_wrong(filepath);
                system("pause");
                break;
            case 2:
                playAudioFile_correct(filepath);
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
