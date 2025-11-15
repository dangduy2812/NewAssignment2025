#include "Ex3.hpp"

/* Phân tích:
   Tình huống: Hỗ trợ nhiều định dạng âm thanh (MP3, FLAC, AAC)
   Vấn đề: Nếu dùng switch-case, khó mở rộng khi thêm codec mới
   Code mẫu: AudioDecoder (abstract), MP3Decoder/FLACDecoder (concrete), DecoderFactory (abstract), concrete factories
*/

// MP3Decoder
bool MP3Decoder::decodeChunk(const Buffer& in, Buffer& out) {
    cout << "[DEBUG] Decoding MP3 chunk of size " << in.size << endl;
    out.size = in.size; // giả lập copy dữ liệu
    return true;
}

// FLACDecoder
bool FLACDecoder::decodeChunk(const Buffer& in, Buffer& out) {
    cout << "[DEBUG] Decoding FLAC chunk of size " << in.size << endl;
    out.size = in.size;
    return true;
}

// MP3Factory
AudioDecoder* MP3DecoderFactory::createDecoder() {
    cout << "[DEBUG] Creating MP3Decoder via Factory\n";
    return new MP3Decoder();
}

// FLACFactory
AudioDecoder* FLACDecoderFactory::createDecoder() {
    cout << "[DEBUG] Creating FLACDecoder via Factory\n";
    return new FLACDecoder();
}

/* Fix:
   Giải pháp:
   - Giải pháp 1: Dùng Abstract Factory
       + Nguyên lý: Factory tạo decoder mà không cần biết concrete type
       + Vì sao chọn: Dễ mở rộng, tuân Open/Closed Principle
*/

void runExercise3() {
    cout << "[DEBUG] Dang chay Exercise 3...\n";

    // Chọn factory (ví dụ FLAC)
    DecoderFactory* factory = new FLACDecoderFactory();
    AudioDecoder* decoder = factory->createDecoder();

    // Giả lập buffer
    Buffer in {nullptr, 1024};
    Buffer out {nullptr, 0};

    decoder->decodeChunk(in, out);

    delete decoder;
    delete factory;
}
