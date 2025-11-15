#include "Ex1.hpp"

/* ==============================
   Phân tích: Multiple Inheritance - Diamond Problem
   - DigitalAsset: base class (licenseID)
   - AudioContent: DigitalAsset + bitrate
   - Playable: DigitalAsset + duration
   - PlayableSong: inherits AudioContent & Playable -> diamond
   Vấn đề: song.licenseID gây ambiguity vì 2 copy DigitalAsset
=================================*/

/* Fix:
   Giải pháp 1: Virtual Inheritance
   - AudioContent và Playable inherit DigitalAsset 'virtual'
   - Đảm bảo chỉ 1 copy DigitalAsset trong PlayableSong
   - Vì sao chọn: loại bỏ ambiguity, duy trì single base instance
*/

class DigitalAsset {
public:
    long licenseID;
};

class AudioContent : virtual public DigitalAsset {
public:
    int bitrate;
};

class Playable : virtual public DigitalAsset {
public:
    int duration;
};

class PlayableSong : public AudioContent, public Playable {
public:
    void showInfo() {
        cout << "licenseID: " << licenseID << ", bitrate: " << bitrate
             << ", duration: " << duration << endl;
    }
};

void runExercise1() {
    cout << "[EX1] Multiple Inheritance - Diamond Problem\n";

    PlayableSong song;
    song.licenseID = 123;
    song.bitrate = 320;
    song.duration = 180;
    cout << "PlayableSong info:\n";
    song.showInfo();
}
/* Giải pháp 2 (không chọn): Sử dụng composition thay vì inheritance
   - PlayableSong chứa AudioContent và Playable như thành viên
   - Tránh diamond problem nhưng code phức tạp hơn
   - Không chọn vì không tận dụng được tính kế thừa đa hình
*/

/* Kết luận:
   - Virtual Inheritance là giải pháp hiệu quả cho diamond problem
   - Giữ code sạch, tránh ambiguity, tận dụng đa hình
*/
