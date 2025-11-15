#include <iostream>
#include <vector>
#include <string>
#include <cmath> // Dùng cho hiệu ứng Reverb

// Giả định: Kích thước của mỗi khối dữ liệu âm thanh
const size_t BUFFER_SIZE = 10; 

/* PHÂN TÍCH

Tình huống:
Cần một hệ thống xử lý âm thanh linh hoạt, cho phép người dùng chọn các hiệu ứng như "Bass Boost" hay "Reverb" để áp dụng theo thời gian thực (real-time).

Yêu cầu:
1. Thiết kế giải pháp dùng Con trỏ hàm (Function Pointers).
2. Định nghĩa kiểu con trỏ hàm AudioEffectCallback (kiểu: void (*)(float*, size_t)).
3. Triển khai 2 hàm hiệu ứng (applyBassBoost, applyReverb) có chữ ký khớp với kiểu trên.
4. Thiết kế bộ xử lý (Processor) có biến thành viên là AudioEffectCallback để lưu hiệu ứng hoạt động.
5. Bộ xử lý phải có khả năng gán và gọi hàm hiệu ứng thông qua con trỏ hàm.

Lý thuyết (Function Pointers):
Con trỏ hàm là một biến lưu trữ địa chỉ của một hàm. Khi được gọi, nó
thực thi hàm tại địa chỉ đó.
- Cú pháp khai báo: `kiểu_trả_về (*tên_con_trỏ)(kiểu_tham_số1, kiểu_tham_số2, ...);`
- Lợi ích:
    - Tính linh hoạt: Cho phép chuyển đổi linh hoạt hàm được gọi trong thời gian chạy (runtime).
    - Giảm khớp nối (Decoupling): Bộ xử lý chính không cần biết chi tiết về các hàm hiệu ứng; nó chỉ cần biết chữ ký (signature) của hàm.
    - Khả năng mở rộng: Khi thêm hiệu ứng mới, chỉ cần viết hàm mới và gán địa chỉ của nó, không cần sửa đổi cấu trúc điều khiển (switch/if-else) trung tâm.
*/

// 1. Định nghĩa Kiểu Con Trỏ Hàm (Function Pointer Type) 
// Yêu cầu: alias tên là AudioEffectCallback cho hàm nhận (float*, size_t) và trả về void.

using AudioEffectCallback = void (*)(float* buffer, size_t size);
// AudioEffectCallback là pointer tới hàm:
// - input: mảng float (audio buffer) + kích thước
// - output: void

// 2. Triển khai Các Hàm Hiệu ứng (Effect Functions) 

/*
 * Hiệu ứng Tăng âm trầm (Bass Boost).
 * Tăng cường biên độ cho toàn bộ buffer.
 */

void applyBassBoost(float* buffer, size_t size) {
    std::cout << "[APPLYING] Bass Boost (+25% gain)" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        // Tăng biên độ 25% (nhân với 1.25)
        buffer[i] *= 1.25f;
        // Giới hạn biên độ để tránh vỡ tiếng (clipping)
        if (buffer[i] > 1.0f) buffer[i] = 1.0f;
        if (buffer[i] < -1.0f) buffer[i] = -1.0f;
    }
}
/*
 * Hiệu ứng Reverb (Mô phỏng đơn giản).
 * Trộn tín hiệu gốc với một tín hiệu bị trễ.
 */
void applyReverb(float* buffer, size_t size) {
    std::cout << "[APPLYING] Simple Reverb (Mixing delayed signal)" << std::endl;
    // Giả định một độ trễ nhỏ (tại đây là 3 mẫu)
    const size_t delay_samples = 3; 
    const float decay = 0.5f; // Mức độ trộn

    for (size_t i = delay_samples; i < size; ++i) {
        // Trộn tín hiệu hiện tại với tín hiệu bị trễ (delay) từ quá khứ
        buffer[i] = buffer[i] + (buffer[i - delay_samples] * decay);
        // Giới hạn biên độ
        if (buffer[i] > 1.0f) buffer[i] = 1.0f;
        if (buffer[i] < -1.0f) buffer[i] = -1.0f;
    }
}
/*
 * Hiệu ứng mặc định: Không làm gì (No Effect).
 * Hàm này chỉ in ra tên hiệu ứng và để dữ liệu âm thanh
 * đi qua mà không thực hiện bất kỳ thay đổi nào.
 */

void applyNoEffect(float* buffer, size_t size) {
    std::cout << "[APPLYING] No Effect (Pass-through)" << std::endl;
    // Không cần code gì ở đây
}


// 3. Thiết kế Bộ Xử Lý (Processor) 

enum AudioEffectType {
    NO_EFFECT,
    BASS_BOOST,
    REVERB
};

class AudioProcessor {
private:
    // Dòng này khai báo một biến thành viên có tên là activeEffect
    // activeEffect là một con trỏ hàm có khả năng trỏ tới bất kỳ hàm nào có chữ ký void (float*, size_t)
    AudioEffectCallback activeEffect;
    /*Chức năng: Biến này đóng vai trò là một cổng chuyển mạch (switch) hoặc biến trạng thái để giữ địa chỉ của hàm hiệu ứng âm thanh hiện tại đang được áp dụng. Bất cứ khi nào bộ xử lý âm thanh cần áp dụng hiệu ứng, nó sẽ gọi hàm thông qua con trỏ này.*/

public:
// Constructor: Khởi tạo bộ xử lý với hiệu ứng mặc định là No Effect
    AudioProcessor() : activeEffect(applyNoEffect) {
        // Mặc định ban đầu là không có hiệu ứng
    }
    /*
    AudioProcessor(): Hàm tạo không tham số của class.
:: Bắt đầu danh sách khởi tạo thành viên.
activeEffect(applyNoEffect): Khởi tạo biến thành viên activeEffect với giá trị là địa chỉ của hàm applyNoEffect.
Hàm applyNoEffect (chắc chắn phải có chữ ký void (float*, size_t)) là một hàm được định nghĩa trước, không làm gì cả (ví dụ: chỉ đơn thuần sao chép dữ liệu hoặc không thay đổi bộ đệm).
    */

/*
     * Gán địa chỉ của hàm hiệu ứng tương ứng cho con trỏ activeEffect.
     */

    void setActiveEffect(AudioEffectType type) {
        std::cout << "\nThay doi hieu ung " << std::endl;
        switch (type) {
            case BASS_BOOST:
                // Gán địa chỉ của hàm applyBassBoost
                activeEffect = applyBassBoost; 
                std::cout << "chon: BASS BOOST" << std::endl;
                break;
            case REVERB:
                // Gán địa chỉ của hàm applyReverb
                activeEffect = applyReverb;
                std::cout << "chon: REVERB" << std::endl;
                break;
            case NO_EFFECT:
            default:
                activeEffect = applyNoEffect;
                std::cout << "chon: NO EFFECT" << std::endl;
                break;
                /*
                Khi user chọn effect, activeEffect trỏ tới hàm tương ứng.
                Không cần gọi switch-case trong vòng lặp chính nữa.
                */
        }
    }

  /*
     * Vòng lặp xử lý âm thanh chính. Gọi hàm thông qua con trỏ hàm.
     */
    void processAudio(float* buffer) {
        std::cout << "  > Xử lý khối dữ liệu #" << (rand() % 100) << ": ";
        // GỌI HÀM THÔNG QUA CON TRỎ: activeEffect(tham số...)
        activeEffect(buffer, BUFFER_SIZE); // BUFFER_SIZE = 10
        // Sau khi gọi, buffer đã được thay đổi bởi hàm được trỏ đến (BassBoost/Reverb/NoEffect)
    }
};


// Hàm mô phỏng việc tạo dữ liệu âm thanh mẫu
void initializeBuffer(float* buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        // Tạo một sóng sin đơn giản (biên độ từ -1.0 đến 1.0)
        buffer[i] = std::sin(i * 0.5f); 
    }
}

int main() {
    // 1. Khởi tạo bộ xử lý
    AudioProcessor processor;

    // 2. Chuẩn bị buffer âm thanh
    float audioBuffer[BUFFER_SIZE];

    // Demo 1: Không có hiệu ứng (Mặc định) 
    processor.setActiveEffect(NO_EFFECT);
    initializeBuffer(audioBuffer, BUFFER_SIZE);
    processor.processAudio(audioBuffer);


    // Demo 2: Áp dụng Bass Boost 
    processor.setActiveEffect(BASS_BOOST);
    // Khởi tạo lại buffer (để đảm bảo Bass Boost áp dụng lên dữ liệu gốc)
    initializeBuffer(audioBuffer, BUFFER_SIZE);
    processor.processAudio(audioBuffer);


    // Demo 3: Áp dụng Reverb 
    processor.setActiveEffect(REVERB);
    // Khởi tạo lại buffer
    initializeBuffer(audioBuffer, BUFFER_SIZE);
    processor.processAudio(audioBuffer);


    return 0;
}
/* LỢI ÍCH CỦA FUNCTION POINTERS (Phân tích):
    1. Tốc độ xử lý (runtime) được tối ưu vì không có overhead của switch-case trong vòng lặp chính.
       Bộ xử lý chỉ gọi 'initializeBuffer(buffer, size);'.
    2. Khả năng mở rộng cao: Khi thêm hiệu ứng mới, chỉ cần viết hàm mới và cập nhật setActiveEffect().
       Hàm xử lý processAudio() không cần chỉnh sửa, tuân thủ nguyên tắc Open/Closed.
    */