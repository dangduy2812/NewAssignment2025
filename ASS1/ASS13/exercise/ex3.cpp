#include "Ex3.hpp"

/* ==============================
   Phân tích: Constructor/Destructor Order & Virtual Destructor
   - MediaObject -> AudioTrack -> LosslessAudioTrack -> FLACFile
   - Mỗi lớp cấp phát tài nguyên
   - Vấn đề: nếu base destructor không virtual, delete ptr base -> derived không giải phóng đầy đủ
=================================*/

class MediaObject {
public:
    MediaObject() { cout << "MediaObject Constructor\n"; }
    virtual ~MediaObject() { cout << "MediaObject Destructor\n"; } // virtual
};

class AudioTrack : public MediaObject {
public:
    AudioTrack() { cout << "AudioTrack Constructor\n"; }
    ~AudioTrack() { cout << "AudioTrack Destructor\n"; }
};

class LosslessAudioTrack : public AudioTrack {
public:
    LosslessAudioTrack() { cout << "LosslessAudioTrack Constructor\n"; }
    ~LosslessAudioTrack() { cout << "LosslessAudioTrack Destructor\n"; }
};

class FLACFile : public LosslessAudioTrack {
public:
    FLACFile() { cout << "FLACFile Constructor\n"; }
    ~FLACFile() { cout << "FLACFile Destructor\n"; }
};

void runExercise3() {
    cout << "[EX3] Constructor/Destructor & Virtual Destructor\n";

    FLACFile file;
    cout << "\n--- Create pointer to base and delete ---\n";
    MediaObject* ptr = new FLACFile();
    delete ptr; // virtual ensures all destructors called
}

/* Giải pháp 2 (không chọn): Không dùng virtual destructor
   - Sử dụng smart pointers (unique_ptr/shared_ptr) để quản lý tài nguyên
   - Tuy nhiên vẫn nên có virtual destructor để an toàn
   - Không chọn vì phức tạp hơn và không giải quyết gốc vấn đề
*/
/* Kết luận:
   - Luôn khai báo destructor base class là virtual nếu lớp có thể kế thừa
   - Đảm bảo tài nguyên được giải phóng đúng cách khi xóa qua con trỏ base
*/
