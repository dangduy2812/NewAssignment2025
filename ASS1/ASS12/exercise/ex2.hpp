#pragma once
#include <iostream>
using namespace std;

// Forward declaration
class Equalizer;

// Class CarAudioSystem
class CarAudioSystem {
private:
    float hardware_volume;
    float hardware_balance;

public:
    CarAudioSystem();
    void increaseVolume(float delta);
    void setBalance(float percent);
    void printStatus() const;

    // Friend class
    friend class Equalizer;
};

// Class Equalizer
class Equalizer {
public:
    void adjustVolumeDirectly(CarAudioSystem& system, float newVolume);
};

// Hàm chạy Exercise 2
void runExercise2();
