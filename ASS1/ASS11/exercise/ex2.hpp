#ifndef EX2_HPP
#define EX2_HPP

#include <iostream>
#include <string>
using namespace std;

// Khai báo trước để friend có thể hoạt động
class Equalizer;

/*
    Class quản lý phần cứng âm thanh của xe
    - Có dữ liệu nhạy cảm như volume, balance...
    - Chỉ các lớp đặc biệt (Equalizer) mới được truy cập trực tiếp
*/
class CarAudioSystem {
private:
    float hardware_volume;
    float hardware_balance;

public:
    CarAudioSystem();

    void increaseVolume(float step);
    void setBalance(float value);
    void showStatus() const;

    // Cho phép lớp Equalizer truy cập trực tiếp các thuộc tính private
    friend class Equalizer;
};

/*
    Lớp Equalizer - được cấp quyền đặc biệt để điều chỉnh sâu
*/
class Equalizer {
public:
    void tuneHardware(CarAudioSystem& system);
};

// Hàm demo chạy bài 2
void runExercise2();

#endif
