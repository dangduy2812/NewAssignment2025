#include "ex3.hpp"
#include <thread>
#include <chrono>

/*
==================================================================
Phân tích: tóm tắt tình huống + code mẫu (nếu có)
------------------------------------------------------------------
Tình huống:
Ứng dụng âm nhạc cần hỗ trợ nhiều định dạng (MP3, FLAC, AAC...).
Mỗi loại yêu cầu bộ giải mã (decoder) khác nhau.

Vấn đề:
Nếu dùng switch-case để chọn loại decoder, mỗi khi thêm định dạng mới
phải sửa lại code trung tâm → vi phạm nguyên tắc Open/Closed.

Code mẫu ban đầu:
if (ext == ".mp3") decoder = new MP3Decoder();
else if (ext == ".flac") decoder = new FLACDecoder();
→ Khó mở rộng, phải sửa code mỗi khi có định dạng mới.
==================================================================
*/

/*
==================================================================
Fix: liệt kê giải pháp
------------------------------------------------------------------
Giải pháp 1: Abstract Factory Pattern
- Lý do: Tách logic tạo đối tượng ra khỏi phần sử dụng.
- Nguyên lý hoạt động: Factory trừu tượng tạo decoder mà không biết
  loại cụ thể nào sẽ được sinh ra.
- Vì sao chọn: Dễ mở rộng, tuân thủ nguyên tắc OCP.

Giải pháp 2: Factory Method
- Cũng có thể dùng, nhưng ít phù hợp hơn vì mỗi loại cần 1 factory riêng.
==================================================================
*/

// ======================= TRIỂN KHAI ==============================

bool MP3Decoder::decodeChunk(const string& in, string& out) {
    cout << "[DEBUG] Dang giai ma MP3 chunk: " << in << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    out = "[MP3 data decoded]";
    return true;
}

bool FLACDecoder::decodeChunk(const string& in, string& out) {
    cout << "[DEBUG] Dang giai ma FLAC chunk: " << in << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    out = "[FLAC data decoded]";
    return true;
}

AudioDecoder* MP3DecoderFactory::createDecoder() {
    cout << "[DEBUG] Tao bo giai ma MP3" << endl;
    return new MP3Decoder();
}

AudioDecoder* FLACDecoderFactory::createDecoder() {
    cout << "[DEBUG] Tao bo giai ma FLAC" << endl;
    return new FLACDecoder();
}

// ======================= DEMO CHÍNH ==============================

void runExercise3() {
    cout << "=== Exercise 3: Abstract Factory Pattern ===" << endl;
    DecoderFactory* factory = nullptr;
    AudioDecoder* decoder = nullptr;

    int choice;
    do {
        cout << "\n1. Chon MP3 Decoder\n";
        cout << "2. Chon FLAC Decoder\n";
        cout << "0. Thoat\n";
        cout << "Chon loai giai ma: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            cout << "[DEBUG] Ban chon MP3DecoderFactory\n";
            factory = new MP3DecoderFactory();
            break;
        case 2:
            cout << "[DEBUG] Ban chon FLACDecoderFactory\n";
            factory = new FLACDecoderFactory();
            break;
        case 0:
            cout << "Thoat bai 3\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }

        if (choice == 1 || choice == 2) {
            decoder = factory->createDecoder();
            string out;
            decoder->decodeChunk("Audio block 1", out);
            cout << "[OUTPUT] Ket qua: " << out << endl;
            delete decoder;
            delete factory;

            cout << "Nhan phim bat ky de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
        }

    } while (choice != 0);

    cout << "=== Ket thuc bai 3 ===" << endl;
}
