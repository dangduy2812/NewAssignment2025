#pragma once
#include <string>
#include <vector>

struct Song {
    std::string title;
    std::string artist;
};

// Phương thức sai: ghi trực tiếp file gốc
bool savePlaylist_wrong(const std::vector<Song>& playlist, const char* filepath);

// Phương thức đúng: ghi file tạm, rename
bool savePlaylist_correct(const std::vector<Song>& playlist, const char* filepath);

// Hiển thị playlist
void printPlaylist(const std::vector<Song>& playlist);

// Menu chạy Exercise 4
void RunEx4();
