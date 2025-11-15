#include "ex4.hpp"
#include <cstdlib> 
/* ================================================================
   PHÂN TÍCH:
   Tình huống: Playlist dùng linked list, cần hàm advanceToNextTrack() 
   để cập nhật pointer nowPlaying tới bài kế tiếp.

   Vấn đề: Nếu viết void advanceToNextTrack(Song* currentTrack) và gán
   currentTrack = currentTrack->next, thì ngoài hàm, pointer nowPlaying 
   vẫn không thay đổi vì:
   - Khi truyền pointer, bản thân pointer được copy (pass-by-value)
   - Thay đổi copy này không ảnh hưởng pointer gốc bên ngoài hàm

   Giải pháp:
   - Cách 1: Truyền **tham chiếu tới pointer** (Song*& currentTrack)
   - Cách 2: Truyền **pointer tới pointer** (Song** currentTrack)
================================================================ */

// Hàm sai: chỉ thay đổi copy của pointer
void advanceToNextTrack_WRONG(Song* currentTrack) {
    std::cout << "Dang chay phuong thuc advanceToNextTrack_WRONG ..." << std::endl;
    if(currentTrack != nullptr)
        currentTrack = currentTrack->next;
}

// Fix 1: reference to pointer
void advanceToNextTrack_REF(Song*& currentTrack) {
    std::cout << "Dang chay phuong thuc advanceToNextTrack_REF ..." << std::endl;
    if(currentTrack != nullptr)
        currentTrack = currentTrack->next;
}

// Fix 2: pointer to pointer
void advanceToNextTrack_PTR(Song** currentTrack) {
    std::cout << "Dang chay phuong thuc advanceToNextTrack_PTR ..." << std::endl;
    if(currentTrack != nullptr && *currentTrack != nullptr)
        *currentTrack = (*currentTrack)->next;
}

/* ================================================================
   Menu chính
================================================================ */
void RunEx4() {
    // Khởi tạo playlist
    Song songA{"Song A"};
    Song songB{"Song B"};
    Song songC{"Song C"};
    songA.next = &songB;
    songB.next = &songC;

    Song* nowPlaying;

    int choice;
    do {
        system("cls");
        std::cout << "=== ASSIGNMENT 4: Passing Pointers vs Modifying Pointer Data ===\n";
        std::cout << "1. Chay ham sai (pass-by-value)\n";
        std::cout << "2. Chay ham dung (reference to pointer)\n";
        std::cout << "3. Chay ham dung (pointer to pointer)\n";
        std::cout << "0. Thoat\n";
        std::cout << "Chon: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                nowPlaying = &songA;
                advanceToNextTrack_WRONG(nowPlaying);
                std::cout << "Now playing: " << nowPlaying->title << std::endl;
                system("pause");
                break;
            case 2:
                nowPlaying = &songA;
                advanceToNextTrack_REF(nowPlaying);
                std::cout << "Now playing: " << nowPlaying->title << std::endl;
                system("pause");
                break;
            case 3:
                nowPlaying = &songA;
                advanceToNextTrack_PTR(&nowPlaying);
                std::cout << "Now playing: " << nowPlaying->title << std::endl;
                system("pause");
                break;
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
   - Truyền pointer bình thường chỉ copy pointer -> thay đổi copy không ảnh hưởng ngoài hàm.
   - Reference to pointer hoặc pointer to pointer cho phép cập nhật pointer gốc.
================================================================ */
