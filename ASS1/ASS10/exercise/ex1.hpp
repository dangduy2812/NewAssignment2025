#pragma once
#include <cstdint>

const int EQ_BANDS = 10;

struct UserSettings {
    int32_t last_volume;
    bool shuffle_mode_enabled;
    uint64_t last_played_track_id;
    float eq_presets[EQ_BANDS];
};

// Phương thức sai
bool saveSettings_wrong(const UserSettings& settings, const char* filepath);
bool loadSettings_wrong(UserSettings& settings, const char* filepath);

// Phương thức đúng
bool saveSettings_correct(const UserSettings& settings, const char* filepath);
bool loadSettings_correct(UserSettings& settings, const char* filepath);

// Hiển thị settings
void printSettings(const UserSettings& s);

// Menu chạy bài Exercise 1
void RunEx1();
