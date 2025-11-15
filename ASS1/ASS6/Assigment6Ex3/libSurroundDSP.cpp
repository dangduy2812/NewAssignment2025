#include <iostream>
extern "C" __declspec(dllexport) void initialize_surround_effect() {
    std::cout << "[SurroundDSP] Plugin loaded successfully! 🎧\n";
}
/* Giả lập thư viện plugin DSP */