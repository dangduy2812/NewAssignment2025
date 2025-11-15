#ifndef EX3_HPP
#define EX3_HPP

#include <string>
#include <iostream>
#include <vector>


struct Song {
    int songID;
    std::string title;
    std::string artist;
};

extern std::vector<Song> g_playlist; // Playlist toàn cục

// Function overloading prototypes
Song* findSongInPlaylist(int songID);
Song* findSongInPlaylist(const std::string& title);

void RunEx3();

#endif
