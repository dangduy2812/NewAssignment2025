#pragma once
#include <string>
#include <vector>

// Struct chứa metadata của bài hát
struct SongMetadata {
    std::string title;
    std::string artist;
    std::string lyrics;
    std::vector<char> albumArtRawData; // Có thể rất lớn
};

// Prototype các hàm
void displayMetadata_WRONG(SongMetadata data);              // Pass-by-value, tốn bộ nhớ
void displayMetadata_CORRECT(const SongMetadata& data);     // Pass-by-const-reference, tối ưu
void onNewSongSelected_WRONG(const SongMetadata& originalSong);
void onNewSongSelected_CORRECT(const SongMetadata& originalSong);
void RunEx1(); // Hàm menu chính

