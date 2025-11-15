#ifndef EX3_HPP
#define EX3_HPP

#include <iostream>
#include <string>
using namespace std;

/*
    Mô hình Abstract Factory cho bộ giải mã âm thanh (Audio Decoder)
    ---------------------------------------------------------------
    - Cho phép tạo ra các đối tượng giải mã (MP3Decoder, FLACDecoder, ...)
      mà không cần biết cụ thể lớp nào sẽ được dùng.
*/

// Lớp interface cho Decoder
class AudioDecoder {
public:
    virtual bool decodeChunk(const string& in, string& out) = 0;
    virtual ~AudioDecoder() = default;
};

// Lớp cụ thể: MP3
class MP3Decoder : public AudioDecoder {
public:
    bool decodeChunk(const string& in, string& out) override;
};

// Lớp cụ thể: FLAC
class FLACDecoder : public AudioDecoder {
public:
    bool decodeChunk(const string& in, string& out) override;
};

// Abstract Factory
class DecoderFactory {
public:
    virtual AudioDecoder* createDecoder() = 0;
    virtual ~DecoderFactory() = default;
};

// Concrete Factory: MP3
class MP3DecoderFactory : public DecoderFactory {
public:
    AudioDecoder* createDecoder() override;
};

// Concrete Factory: FLAC
class FLACDecoderFactory : public DecoderFactory {
public:
    AudioDecoder* createDecoder() override;
};

// Hàm demo chính của bài 3
void runExercise3();

#endif
