#include "ex3.hpp"
#include <cstdlib> 
/* ================================================================
   PHÂN TÍCH:
   Tình huống: Ứng dụng cần tìm bài hát trong playlist theo nhiều tiêu chí:
   - Theo songID (int)
   - Theo title (string)

   Vấn đề: Nếu dùng 1 hàm với void* + kiểu dữ liệu, lập trình sẽ khó và dễ lỗi.

   Giải pháp:
   - Sử dụng function overloading:
     + Song* findSongInPlaylist(int songID)
     + Song* findSongInPlaylist(const std::string& title)
   - Compiler sẽ tự chọn hàm đúng dựa trên kiểu tham số. Quá trình này gọi là *compile-time polymorphism* (static binding).
================================================================ */

// Playlist toàn cục
std::vector<Song> g_playlist = {
    {101, "Bohemian Rhapsody", "Queen"},
    {102, "Imagine", "John Lennon"},
    {103, "Stairway to Heaven", "Led Zeppelin"}
};

// Tìm theo songID
Song* findSongInPlaylist(int songID) {
    std::cout << "Dang chay phuong thuc findSongInPlaylist(int) ..." << std::endl;
    for(auto& song : g_playlist) {
        if(song.songID == songID)
            return &song;
    }
    return nullptr;
}

// Tìm theo title
Song* findSongInPlaylist(const std::string& title) {
    std::cout << "Dang chay phuong thuc findSongInPlaylist(string) ..." << std::endl;
    for(auto& song : g_playlist) {
        if(song.title == title)
            return &song;
    }
    return nullptr;
}

/* ================================================================
   Menu chính
================================================================ */
void RunEx3() {
    int choice;
    do {
        system("cls");
        std::cout << "=== ASSIGNMENT 3: Function Overloading for Playlist Searches ===\n";
        std::cout << "1. Tim bai hat theo songID (101)\n";
        std::cout << "2. Tim bai hat theo title (\"Bohemian Rhapsody\")\n";
        std::cout << "0. Thoat\n";
        std::cout << "Chon: ";
        std::cin >> choice;

        switch(choice) {
            case 1: {
                Song* s = findSongInPlaylist(101);
                if(s)
                    std::cout << "Tim thay: " << s->title << " - " << s->artist << std::endl;
                else
                    std::cout << "Khong tim thay bai hat!\n";
                system("pause");
                break;
            }
            case 2: {
                std::cin.ignore(); // xóa newline còn lại
                Song* s = findSongInPlaylist("Bohemian Rhapsody");
                if(s)
                    std::cout << "Tim thay: " << s->title << " - " << s->artist << std::endl;
                else
                    std::cout << "Khong tim thay bai hat!\n";
                system("pause");
                break;
            }
            case 0:
                std::cout << "Thoat chuong trinh.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le!\n";
                system("pause");
        }
    } while(choice != 0);
}

/* ================================================================
   Giải thích:
   - Compiler chọn hàm đúng dựa trên kiểu tham số: int hay string.
   - Quá trình này gọi là function overloading, compile-time polymorphism.
================================================================ */
