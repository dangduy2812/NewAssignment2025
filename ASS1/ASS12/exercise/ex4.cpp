#include "Ex4.hpp"

/* Phân tích:
   Tình huống: Import playlist nhiều định dạng (.txt, .xml)
   Vấn đề: Các bước chung giống nhau, nhưng parseContents và validateSongs khác nhau
   Code mẫu: PlaylistImporter (abstract), TxtPlaylistImporter, XmlPlaylistImporter
*/

// Template Method implementation
void PlaylistImporter::importFromFile(const char* path) {
    cout << "[DEBUG] Starting import from file: " << path << endl;
    if(!open(path)) { cout << "[DEBUG] Failed to open file\n"; return; }
    if(!parseContents()) { cout << "[DEBUG] Failed to parse contents\n"; return; }
    if(!validateSongs()) { cout << "[DEBUG] Validation failed\n"; return; }
    addToLibrary();
    close();
    cout << "[DEBUG] Import completed\n";
}

// Default implementations
bool PlaylistImporter::open(const char* path) { 
    cout << "[DEBUG] Open file: " << path << endl; 
    return true; 
}

void PlaylistImporter::addToLibrary() { 
    cout << "[DEBUG] Adding songs to library...\n"; 
}

void PlaylistImporter::close() { 
    cout << "[DEBUG] Closing file\n"; 
}

// TxtPlaylistImporter
bool TxtPlaylistImporter::parseContents() { 
    cout << "[DEBUG] Parsing TXT playlist\n"; 
    return true; 
}

bool TxtPlaylistImporter::validateSongs() { 
    cout << "[DEBUG] Validating TXT playlist\n"; 
    return true; 
}

// XmlPlaylistImporter
bool XmlPlaylistImporter::parseContents() { 
    cout << "[DEBUG] Parsing XML playlist\n"; 
    return true; 
}

bool XmlPlaylistImporter::validateSongs() { 
    cout << "[DEBUG] Validating XML playlist\n"; 
    return true; 
}

/* Fix:
   Giải pháp:
   - Giải pháp 1: Template Method Pattern
       + Nguyên lý: Định nghĩa khung thuật toán trong base class, subclass override các bước riêng
       + Vì sao chọn: Tái sử dụng code, enforce flow chung, dễ mở rộng định dạng mới
*/

void runExercise4() {
    cout << "[DEBUG] Dang chay Exercise 4...\n";

    TxtPlaylistImporter txtImporter;
    txtImporter.importFromFile("playlist.txt");

    XmlPlaylistImporter xmlImporter;
    xmlImporter.importFromFile("playlist.xml");
}
