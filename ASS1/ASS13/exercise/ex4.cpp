#include "Ex4.hpp"

/* ==============================
   Phân tích: Object Slicing
   - MediaItem base class, Song derived
   - std::vector<MediaItem> lưu đối tượng by value -> slicing
   - Vấn đề: thông tin Song bị mất, play() gọi base version
=================================*/

class MediaItem {
public:
    virtual void play() const { cout << "Playing generic media\n"; }
    virtual ~MediaItem() {}
};

class Song : public MediaItem {
public:
    string artist;
    void play() const override { cout << "Playing song of " << artist << endl; }
};

void runExercise4() {
    cout << "[EX4] Object Slicing\n";

    vector<unique_ptr<MediaItem>> playlist;

    auto s = make_unique<Song>();
    s->artist = "Queen";

    playlist.push_back(move(s));

    for (const auto& item : playlist) {
        item->play(); // polymorphic behavior preserved
    }
}
