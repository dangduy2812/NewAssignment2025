#ifndef EX1_HPP
#define EX1_HPP

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// Abstract class đại diện cho nguồn âm thanh chung
class AudioSource {
public:
    virtual bool open(const char* source_path) = 0;
    virtual size_t read(char* buffer, size_t bytes_to_read) = 0;
    virtual bool seek(long offset) = 0;
    virtual void close() = 0;
    virtual ~AudioSource() {}
};

// Lớp kế thừa cụ thể: đọc file nhạc từ ổ đĩa
class LocalFileSource : public AudioSource {
private:
    FILE* file;
public:
    LocalFileSource() : file(nullptr) {}
    bool open(const char* source_path) override;
    size_t read(char* buffer, size_t bytes_to_read) override;
    bool seek(long offset) override;
    void close() override;
};

// Hàm chạy demo cho bài 1
void runExercise1();

#endif
