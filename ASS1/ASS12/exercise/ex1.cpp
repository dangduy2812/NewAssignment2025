#include "Ex1.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

/* Phân tích: 
   Tình huống: Cần phát nhạc từ nhiều nguồn khác nhau (file, bluetooth, radio)
   Code mẫu: AudioSource (abstract), LocalFileSource (concrete)
   Vấn đề: Nếu không dùng abstract class, player engine phải dùng nhiều if-else, khó mở rộng
*/

LocalFileSource::LocalFileSource() : file(nullptr) {}
LocalFileSource::~LocalFileSource() { if(file) fclose(file); }

bool LocalFileSource::open(const char* source_path) {
    cout << "[DEBUG] Open file: " << source_path << endl;
    file = fopen(source_path, "rb");
    return file != nullptr;
}

size_t LocalFileSource::read(char* buffer, size_t bytes_to_read) {
    if(!file) return 0;
    return fread(buffer, 1, bytes_to_read, file);
}

bool LocalFileSource::seek(long offset) {
    if(!file) return false;
    return fseek(file, offset, SEEK_SET) == 0;
}

void LocalFileSource::close() {
    if(file) {
        fclose(file);
        file = nullptr;
    }
}

/* Fix: 
   Giải pháp: Dùng abstract class
   Giải pháp 1: AudioSource + LocalFileSource
       - Nguyên lý: Player engine dùng AudioSource* mà không biết concrete type
       - Lý do chọn: Đảm bảo mở rộng, tuân theo Open/Closed Principle
*/

void runExercise1() {
    cout << "[DEBUG] Dang chay Exercise 1...\n";

    LocalFileSource local;
    if(local.open("test_audio.mp3")) {
        cout << "[DEBUG] File opened successfully.\n";
        char buffer[128];
        size_t read_bytes = local.read(buffer, sizeof(buffer));
        cout << "[DEBUG] Read " << read_bytes << " bytes from file.\n";

        local.seek(0);
        cout << "[DEBUG] Seeked to beginning.\n";

        local.close();
        cout << "[DEBUG] File closed.\n";
    } else {
        cout << "[DEBUG] Failed to open file.\n";
    }
}
