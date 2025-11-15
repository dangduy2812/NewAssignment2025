#include "ex2.hpp"
#include <thread>
#include <chrono>
#include <cstdlib>

/*
==================================================================
Phân tích: tóm tắt tình huống + code mẫu (nếu có)
------------------------------------------------------------------
Tình huống:
Hệ thống âm thanh trên xe (CarAudioSystem) có các thông số nhạy cảm
như volume và balance. Các thuộc tính này cần được bảo vệ (private)
để tránh hư hại phần cứng hoặc giảm chất lượng âm thanh.

Vấn đề:
Một lớp đặc biệt (Equalizer) cần truy cập trực tiếp các thông số này
để điều chỉnh chi tiết, nhưng việc mở public sẽ phá vỡ tính đóng gói.

Code mẫu (tình huống ban đầu):
class CarAudioSystem { public: float hardware_volume; } // nguy hiểm
==================================================================
*/

/*
==================================================================
Fix: liệt kê giải pháp
------------------------------------------------------------------
Giải pháp 1: Dùng friend class
- Lý do: Cho phép một lớp cụ thể (Equalizer) truy cập trực tiếp
  vào private/protected của lớp khác.
- Nguyên lý: "friend" không phải là kế thừa, mà là quyền đặc biệt
  được cấp cho lớp được chỉ định.
- Vì sao chọn: giữ tính đóng gói cho phần còn lại của hệ thống,
  nhưng vẫn cho phép Equalizer thao tác cần thiết.

Giải pháp 2: Dùng getter/setter công khai
- Lý do: Cung cấp truy cập gián tiếp, an toàn hơn.
- Tuy nhiên trong trường hợp Equalizer cần can thiệp sâu,
  friend là hợp lý để tránh overhead không cần thiết.
==================================================================
*/

// ======================= TRIỂN KHAI ==============================

CarAudioSystem::CarAudioSystem()
    : hardware_volume(0.5f), hardware_balance(0.0f) {}

void CarAudioSystem::increaseVolume(float step) {
    hardware_volume += step;
    if (hardware_volume > 1.0f) hardware_volume = 1.0f;
    cout << "[DEBUG] Tang volume, gia tri hien tai: " << hardware_volume << endl;
}

void CarAudioSystem::setBalance(float value) {
    if (value < -1.0f) value = -1.0f;
    if (value > 1.0f) value = 1.0f;
    hardware_balance = value;
    cout << "[DEBUG] Dat can bang trai-phai: " << hardware_balance << endl;
}

void CarAudioSystem::showStatus() const {
    cout << "Volume: " << hardware_volume
         << " | Balance: " << hardware_balance << endl;
}

void Equalizer::tuneHardware(CarAudioSystem& system) {
    cout << "[DEBUG] Equalizer dang tinh chinh truc tiep..." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));

    // Truy cập trực tiếp vào biến private nhờ friend
    system.hardware_volume = 0.8f;
    system.hardware_balance = 0.1f;
    cout << "[DEBUG] Da dieu chinh truc tiep volume va balance" << endl;
}

// ======================= DEMO CHÍNH ==============================

void runExercise2() {
    cout << "=== Exercise 2: Friend Class Demo ===" << endl;
    CarAudioSystem systemCar;
    Equalizer eq;

    int choice;
    do {
        cout << "\n1. Chay phien ban sai (khong friend)\n";
        cout << "2. Chay phien ban dung (friend duoc cap quyen)\n";
        cout << "0. Thoat\n";
        cout << "Chon che do: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            cout << "[DEBUG] Dang mo phong phien ban sai...\n";
            cout << "Khong co quyen truy cap truc tiep -> loi bien dich\n";
            cout << "(Demo bo qua vi khong the bien dich trong C++)\n";
            break;
        case 2:
            cout << "[DEBUG] Dang mo phong phien ban dung...\n";
            systemCar.showStatus();
            eq.tuneHardware(systemCar);
            systemCar.showStatus();
            break;
        case 0:
            cout << "Thoat bai 2\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }

        if (choice != 0) {
            cout << "Nhan phim bat ky de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
        }

    } while (choice != 0);

    cout << "=== Ket thuc bai 2 ===" << endl;
}
