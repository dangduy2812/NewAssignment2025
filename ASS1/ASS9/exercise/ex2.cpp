#include "ex2.hpp"
#include <cstdlib> 

using namespace std;
/* ================================================================
   PHÂN TÍCH:
   Tình huống: Ứng dụng cần hàm startPlayback() để phát bài hát.
   Yêu cầu hỗ trợ:
   - Phát từ thời điểm tùy chọn (milliseconds)
   - Áp dụng hiệu ứng fade-in (milliseconds)

   Vấn đề: Nếu tạo quá nhiều hàm overload cho mỗi trường hợp
   sẽ gây trùng lặp code, khó quản lý.

   Giải pháp:
   - Sử dụng default arguments: tham số mặc định cho startTime và fadeInDuration
   - Cho phép gọi hàm với các tùy chọn linh hoạt mà không cần overload nhiều lần
================================================================ */
// Hàm startPlayback với default arguments
void startPlayback(Track* track, int startTime, int fadeInDuration) {
    std::cout << "Dang chay phuong thuc startPlayback ...\n";
    std::cout << "Phat bai hat: " << track->title << " - " << track->artist << "\n";
    std::cout << "StartTime: " << startTime << "ms\n";
    if(fadeInDuration > 0)
        std::cout << "Ap dung fade-in: " << fadeInDuration << "ms\n";
    else
        std::cout << "Khong ap dung fade-in\n";
}

/* ================================================================
   Menu chính
================================================================ */
void RunEx2() {
    Track myTrack;
    myTrack.title = "Bohemian Rhapsody";
    myTrack.artist = "Queen";

    int choice;
    do {
        system("cls");
        std::cout << "=== ASSIGNMENT 2: Flexible API with Default Arguments ===\n";
        std::cout << "1. Phat bai hat tu dau, khong fade-in\n";
        std::cout << "2. Phat bai hat tu dau, fade-in 500ms\n";
        std::cout << "3. Phat bai hat tu 30000ms, fade-in 1000ms\n";
        std::cout << "0. Thoat\n";
        std::cout << "Chon: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                startPlayback(&myTrack); // dung default arguments
                system("pause");
                break;
            case 2:
                startPlayback(&myTrack, 0, 500);
                system("pause");
                break;
            case 3:
                startPlayback(&myTrack, 30000, 1000);
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
   Lưu ý lý thuyết:
   - Tham số default phải đặt ở cuối danh sách tham số.
   - Nếu để giữa sẽ gây lỗi khi gọi hàm mà bỏ qua tham số.
================================================================ */