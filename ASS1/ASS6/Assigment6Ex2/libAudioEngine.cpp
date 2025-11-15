// libAudioEngine.cpp
#include <iostream>

// Khai báo hàm từ libUtils
void printUtilVersion();

void audioInit() {
    std::cout << "[libAudioEngine] Initializing Audio Engine..." << std::endl;
    printUtilVersion(); // Gọi libUtils v2 (được build riêng)
}
