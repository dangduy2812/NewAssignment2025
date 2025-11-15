#pragma once
#include <string>
#include <vector>

struct Song {
    std::string title;
    std::string filePath;
    int duration; // giây
};

// Phương thức sai: parser đơn giản, không kiểm tra lỗi
std::vector<Song> loadPlaylist_wrong(const char* filepath);

// Phương thức đúng: parser robust
std::vector<Song> loadPlaylist_correct(const char* filepath);

// Hiển thị playlist
void printPlaylist(const std::vector<Song>& playlist);

// Menu chạy Exercise 2
void RunEx2();
