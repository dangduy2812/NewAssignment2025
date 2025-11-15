#pragma once
#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class
class PlaylistImporter {
public:
    // Template Method
    void importFromFile(const char* path);

protected:
    virtual bool open(const char* path);
    virtual bool parseContents() = 0;    // phải override
    virtual bool validateSongs() = 0;    // phải override
    virtual void addToLibrary();
    virtual void close();
};

// Concrete Classes
class TxtPlaylistImporter : public PlaylistImporter {
protected:
    bool parseContents() override;
    bool validateSongs() override;
};

class XmlPlaylistImporter : public PlaylistImporter {
protected:
    bool parseContents() override;
    bool validateSongs() override;
};

// Hàm chạy Exercise 4
void runExercise4();
