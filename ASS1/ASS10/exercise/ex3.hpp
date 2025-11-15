#pragma once
#include <string>

const size_t BUFFER_SIZE = 4096; // 4KB

// Phương thức sai: đọc toàn bộ file cùng lúc
void playAudioFile_wrong(const char* filepath);

// Phương thức đúng: đọc theo chunks
void playAudioFile_correct(const char* filepath);

// Menu chạy Exercise 3
void RunEx3();
