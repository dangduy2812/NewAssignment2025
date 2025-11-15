#ifndef EX4_HPP
#define EX4_HPP

#include <iostream>

struct Song {
    std::string title;
    Song* next = nullptr;
};

// Hàm sai
void advanceToNextTrack_WRONG(Song* currentTrack);

// Fix phương pháp 1: reference to pointer
void advanceToNextTrack_REF(Song*& currentTrack);

// Fix phương pháp 2: pointer to pointer
void advanceToNextTrack_PTR(Song** currentTrack);

void RunEx4();

#endif
