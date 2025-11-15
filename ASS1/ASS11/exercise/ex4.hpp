#ifndef EX4_HPP
#define EX4_HPP

#include <iostream>
#include <string>
using namespace std;

/*
    Template Method Pattern cho Playlist Importer
    ---------------------------------------------
    - Tái sử dụng luồng xử lý chung (open, parse, validate, addToLibrary, close)
      giữa nhiều định dạng (TXT, XML)
    - Cho phép các bước khác biệt (parse, validate) được tùy chỉnh bởi lớp con.
*/

class PlaylistImporter {
public:
    virtual ~PlaylistImporter() = default;

    // Template Method - định nghĩa khung xử lý chung
    void importFromFile(const string& path);

protected:
    virtual bool open(const string& path);
    virtual bool parseContents() = 0;
    virtual bool validateSongs() = 0;
    virtual void addToLibrary();
    virtual void close();
};

// TXT importer
class TxtPlaylistImporter : public PlaylistImporter {
protected:
    bool parseContents() override;
    bool validateSongs() override;
};

// XML importer
class XmlPlaylistImporter : public PlaylistImporter {
protected:
    bool parseContents() override;
    bool validateSongs() override;
};

// Hàm chạy chính
void runExercise4();

#endif
