#include <iostream>
#include <cstdint> // Cho kieu uint32_t
#include <string>

/* PHÂN TÍCH VÀ LÝ THUYẾT
TÌNH HUỐNG:
Hệ thống ô tô cần bảo vệ dữ liệu ở ba cấp độ khác nhau bằng cách sử dụng từ khóa 'const'
với con trỏ.

LÝ THUYẾT: VỊ TRÍ CỦA CONST
Trong khai báo con trỏ, vị trí của 'const' quyết định đối tượng nào được bảo vệ:

1. const T* p: "Con trỏ TỚI Dữ liệu HẰNG" (Pointer to Constant Data).
   - Const đứng trước loại dữ liệu (T).
   - Ý nghĩa: Dữ liệu (T) là HẰNG. Không thể thay đổi giá trị tại địa chỉ đó (*p).
   - ĐƯỢC PHÉP: Thay đổi con trỏ p (p = dia_chi_khac;).

2. T* const p: "Con trỏ HẰNG tới Dữ liệu" (Constant Pointer to Data).
   - Const đứng sau dấu * (sau con trỏ).
   - Ý nghĩa: Con trỏ (p) là HẰNG. Không thể thay đổi địa chỉ mà con trỏ đang lưu trữ (p = dia_chi_khac;).
   - ĐƯỢC PHÉP: Thay đổi giá trị tại địa chỉ đó (*p = gia_tri_moi;).

3. const T* const p: "Con trỏ HẰNG tới Dữ liệu HẰNG" (Constant Pointer to Constant Data).
   - Const xuất hiện cả hai vị trí.
   - Ý nghĩa: Cả DỮ LIỆU và CON TRỎ đều là HẰNG. Không thể thay đổi giá trị (*p) hay địa chỉ (p).
*/

// Định nghĩa cấu trúc cho Scenario 3
struct Config {
    int version;
    std::string device_name;
};

// Sử dụng namespace để minh họa các Scenario
namespace ConstPointerExamples {

    // --- Scenario 1: Pointer to Constant Data (Bảo vệ dữ liệu, cho phép thay đổi con trỏ) ---
    // Yêu cầu: Không được sửa giá trị tại địa chỉ, nhưng con trỏ có thể trỏ đi nơi khác.
    // Ví dụ: Thanh ghi phần cứng (DAC Register)
    void scenario_1() {
        std::cout << "--- Scenario 1: Const Data (const T*) ---" << std::endl;
        uint32_t dac_value = 0xAA;
        uint32_t other_register = 0xBB;
        
        // Khai báo: Con trỏ tới uint32_t HẰNG (uint32_t là HẰNG)
        const uint32_t* dac_register_ptr = &dac_value;
        
        std::cout << "Gia tri ban dau: " << std::hex << *dac_register_ptr << std::endl;
        
        // KIỂM TRA HÀNH ĐỘNG
        
        // 1. Thử thay đổi dữ liệu (PHẢI THẤT BẠI khi biên dịch)
        // Lỗi biên dịch: *dac_register_ptr = 0xCC; 
        
        // 2. Thử thay đổi con trỏ (PHẢI THÀNH CÔNG)
        dac_register_ptr = &other_register; 
        std::cout << "Gia tri sau khi doi con tro: " << std::hex << *dac_register_ptr << std::endl;
        std::cout << "Ket qua: Du lieu duoc bao ve, con tro duoc phep doi." << std::endl;
    }

    // --- Scenario 2: Constant Pointer to Data (Bảo vệ con trỏ, cho phép thay đổi dữ liệu) ---
    // Yêu cầu: Không được thay đổi địa chỉ của con trỏ, nhưng dữ liệu có thể được sửa.
    // Ví dụ: Con trỏ tới buffer âm thanh đang hoạt động.
    void scenario_2() {
        std::cout << "\n--- Scenario 2: Const Pointer (T* const) ---" << std::endl;
        float audio_buffer[3] = {1.0f, 2.0f, 3.0f};
        float other_buffer[3] = {0.1f, 0.2f, 0.3f};
        
        // Khai báo: Con trỏ HẰNG tới float
        float* const active_audio_buffer = audio_buffer;
        
        std::cout << "Gia tri ban dau: " << active_audio_buffer[0] << std::endl;
        
        // KIỂM TRA HÀNH ĐỘNG
        
        // 1. Thử thay đổi dữ liệu (PHẢI THÀNH CÔNG)
        active_audio_buffer[0] = 5.5f; 
        std::cout << "Gia tri sau khi sua du lieu: " << active_audio_buffer[0] << std::endl;
        
        // 2. Thử thay đổi con trỏ (PHẢI THẤT BẠI khi biên dịch)
        // Lỗi biên dịch: active_audio_buffer = other_buffer; 
        
        std::cout << "Ket qua: Con tro duoc bao ve, du lieu duoc phep sua." << std::endl;
    }

    // --- Scenario 3: Constant Pointer to Constant Data (Bảo vệ cả hai) ---
    // Yêu cầu: Không được thay đổi dữ liệu VÀ không được thay đổi địa chỉ con trỏ.
    // Ví dụ: Dữ liệu cấu hình chỉ đọc từ ROM.
    void scenario_3() {
        std::cout << "\n--- Scenario 3: Const Data & Const Pointer (const T* const) ---" << std::endl;
        Config config_data = {1, "ECU_Primary"};
        Config other_config = {2, "ECU_Secondary"};
        
        // Khai báo: Con trỏ HẰNG tới Config HẰNG
        const Config* const rom_config = &config_data;
        
        std::cout << "Version ban dau: " << rom_config->version << std::endl;

        // KIỂM TRA HÀNH ĐỘNG
        
        // 1. Thử thay đổi dữ liệu (PHẢI THẤT BẠI khi biên dịch)
        // Lỗi biên dịch: rom_config->version = 99; 
        
        // 2. Thử thay đổi con trỏ (PHẢI THẤT BẠI khi biên dịch)
        // Lỗi biên dịch: rom_config = &other_config; 
        
        std::cout << "Ket qua: Ca du lieu va con tro deu duoc bao ve." << std::endl;
    }
}


int main() {
    // Để chứng minh rằng các lỗi biên dịch (Lỗi biên dịch) là đúng,
    // tôi sẽ comment (ghi chú) các dòng code gây ra lỗi.

    ConstPointerExamples::scenario_1();
    ConstPointerExamples::scenario_2();
    ConstPointerExamples::scenario_3();

    return 0;
}