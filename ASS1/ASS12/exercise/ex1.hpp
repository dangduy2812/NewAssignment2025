#pragma once
#include <cstddef> // size_t

// Abstract Base Class
class AudioSource {
public:
    virtual bool open(const char* source_path) = 0;
    virtual size_t read(char* buffer, size_t bytes_to_read) = 0;
    virtual bool seek(long offset) = 0;
    virtual void close() = 0;

    virtual ~AudioSource() {}
};

// Concrete Class
class LocalFileSource : public AudioSource {
private:
    FILE* file;
public:
    LocalFileSource();
    ~LocalFileSource();

    bool open(const char* source_path) override;
    size_t read(char* buffer, size_t bytes_to_read) override;
    bool seek(long offset) override;
    void close() override;
};

// Hàm chạy Exercise 1
void runExercise1();
