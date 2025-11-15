#pragma once
#include <iostream>
#include <string>
using namespace std;

// Buffer struct giả lập
struct Buffer {
    char* data;
    size_t size;
};

// Abstract Decoder Interface
class AudioDecoder {
public:
    virtual bool decodeChunk(const Buffer& in, Buffer& out) = 0;
    virtual ~AudioDecoder() {}
};

// Concrete Decoders
class MP3Decoder : public AudioDecoder {
public:
    bool decodeChunk(const Buffer& in, Buffer& out) override;
};

class FLACDecoder : public AudioDecoder {
public:
    bool decodeChunk(const Buffer& in, Buffer& out) override;
};

// Abstract Factory
class DecoderFactory {
public:
    virtual AudioDecoder* createDecoder() = 0;
    virtual ~DecoderFactory() {}
};

// Concrete Factories
class MP3DecoderFactory : public DecoderFactory {
public:
    AudioDecoder* createDecoder() override;
};

class FLACDecoderFactory : public DecoderFactory {
public:
    AudioDecoder* createDecoder() override;
};

// Hàm chạy Exercise 3
void runExercise3();
