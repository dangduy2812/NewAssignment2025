#pragma once
#include <string>
#include <iostream>


struct Track {
    std::string title;
    std::string artist;
};

void startPlayback(Track* track, int startTime = 0, int fadeInDuration = 0);

void RunEx2();


