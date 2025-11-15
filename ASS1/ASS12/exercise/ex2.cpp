#include "Ex2.hpp"

/* Phân tích:
   Tình huống: Quản lý âm lượng, balance của hệ thống ô tô
   Vấn đề: Một số class cần truy cập trực tiếp dữ liệu private, nếu public sẽ phá vỡ encapsulation
   Code mẫu: CarAudioSystem (private), Equalizer (friend)
*/

// CarAudioSystem implementation
CarAudioSystem::CarAudioSystem() : hardware_volume(50.0f), hardware_balance(0.0f) {}

void CarAudioSystem::increaseVolume(float delta) {
    hardware_volume += delta;
    if(hardware_volume > 100.0f) hardware_volume = 100.0f;
    if(hardware_volume < 0.0f) hardware_volume = 0.0f;
    cout << "[DEBUG] Volume increased to " << hardware_volume << endl;
}

void CarAudioSystem::setBalance(float percent) {
    hardware_balance = percent;
    if(hardware_balance > 100.0f) hardware_balance = 100.0f;
    if(hardware_balance < -100.0f) hardware_balance = -100.0f;
    cout << "[DEBUG] Balance set to " << hardware_balance << endl;
}

void CarAudioSystem::printStatus() const {
    cout << "[DEBUG] Volume: " << hardware_volume << ", Balance: " << hardware_balance << endl;
}

// Equalizer implementation
void Equalizer::adjustVolumeDirectly(CarAudioSystem& system, float newVolume) {
    system.hardware_volume = newVolume; // truy cập trực tiếp nhờ friend
    cout << "[DEBUG] Equalizer directly set volume to " << system.hardware_volume << endl;
}

/* Fix:
   Giải pháp:
   - Giải pháp 1: Dùng phương thức public tăng/giam volume
       + Nguyên lý: Kiểm soát giá trị hợp lệ
       + Vì sao chọn: An toàn, tuân encapsulation
   - Giải pháp 2: Dùng friend class (Equalizer)
       + Nguyên lý: Cho phép truy cập trực tiếp private
       + Vì sao chọn: Cần cho thuật toán xử lý đặc biệt
*/

void runExercise2() {
    cout << "[DEBUG] Dang chay Exercise 2...\n";

    CarAudioSystem car;
    car.printStatus();

    car.increaseVolume(20.0f);
    car.setBalance(30.0f);
    car.printStatus();

    Equalizer eq;
    eq.adjustVolumeDirectly(car, 75.0f);
    car.printStatus();
}
