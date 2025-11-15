// libUI.cpp
#include <iostream>

// Khai báo hàm từ libUtils
void printUtilVersion();

void uiInit() {
    std::cout << "[libUI] Initializing UI..." << std::endl;
    printUtilVersion(); // Gọi libUtils v1 (được build riêng)
}
