#include "Ex2.hpp"

/* ==============================
   Phân tích: Method Overriding & Access Level
   - GenericAudioSource::connect() public
   - BluetoothSource: muốn pairAndConnect() public
   - Vấn đề: bt->connect() phải bị chặn
=================================*/

/* Fix:
   Giải pháp 1: Override connect() và để private
   - C++ cho phép giảm access level khi override
   - pairAndConnect() vẫn gọi được connect()
*/

class GenericAudioSource {
public:
    virtual void connect() { cout << "Generic connection\n"; }
};

class BluetoothSource : public GenericAudioSource {
public:
    void pairAndConnect() {
        cout << "Pairing...\n";
        connect(); // OK: gọi connect nội bộ
        cout << "Connected.\n";
    }
private:
    void connect() override { cout << "Bluetooth internal connect\n"; }
};

void runExercise2() {
    cout << "[EX2] Method Overriding & Access Level\n";

    BluetoothSource bt;
    bt.pairAndConnect();

    // bt.connect(); // <- compile error, access private
}
/* Giải pháp 2 (không chọn): Sử dụng composition thay vì inheritance
   - BluetoothSource chứa GenericAudioSource như thành viên
   - Không bị ràng buộc access level của kế thừa
   - Không chọn vì mất tính đa hình và kế thừa
*/
/* Kết luận:
   - Giảm access level khi override là hợp lệ và hữu ích
   - Giữ tính đóng gói trong khi vẫn cho phép truy cập nội bộ
*/
