#include <iostream>
#include "flac_codec.h"

/* Phân tích:
Scenario:
   Ứng dụng nhạc trong xe hơi cần chơi định dạng FLAC.
   Bạn tích hợp thư viện libFLAC theo 2 cách:
      - Static Linking: libFLAC.a
      - Dynamic Linking: libFLAC.so / libFLAC.dll

   Yêu cầu phân tích:
   1) So sánh kích thước file thực thi giữa static và dynamic linking.
   Static: 
   - Mã thư viện được nhúng trực tiếp.
   - Mã máy của thư viện (libFLAC.a) được sao chép toàn bộ vào file thực thi cuối cùng.
   => Kích thước file thực thi lớn hơn.
   Dynamic:
   - Mã thư viện được để riêng trong file .so / .dll.
   - File thực thi chỉ chứa các tham chiếu và thông tin cần thiết để Loader tìm và nạp thư viện động (libFLAC.so) khi chạy.
   => Kích thước file thực thi nhỏ hơn.

   Kết luận: Liên kết tĩnh tiêu tốn nhiều bộ nhớ Flash (ROM) hơn cho mỗi ứng dụng, trong khi liên kết động tối ưu hóa dung lượng lưu trữ trên Flash.

   2) So sánh RAM sử dụng khi chạy.  
      - Static: 
      Kịch bản : 
      Chỉ 1 ứng dụng dùng libFLAC => RAM sử dụng ít hơn vì mã thư viện đã được nhúng sẵn.
      Nhiều ứng dụng cùng dùng libFLAC => Mỗi ứng dụng tải một bản sao riêng của mã libFLAC vào RAM.
      
      - Dynamic: 
      Kịch bản : Chỉ 1 ứng dụng dùng libFLAC => Tải mã thư viện vào RAM 1 lần cùng với ứng dụng.
      Nhiều ứng dụng cùng dùng libFLAC => Hệ điều hành chỉ tải mã thư viện vào RAM 1 lần và chia sẻ các trang bộ nhớ đó cho tất cả các ứng dụng sử dụng.

      Kết luận: Liên kết động có khả năng tối ưu hóa tổng mức sử dụng RAM tốt hơn nhiều khi nhiều ứng dụng cần cùng một thư viện, giúp tiết kiệm tài nguyên hệ thống quan trọng trong xe ô tô.

   3) Giải thích vì sao static an toàn hơn trong xe hơi.  
      Liên kết tĩnh được ưu tiên cho các hệ thống nhúng quan trọng (mission-critical) như ô tô vì nó mang lại sự đảm bảo về tính toàn vẹn (Integrity) và tính xác định (Determinism) cao hơn:

Loại bỏ Rủi ro Phụ thuộc (Dependency Risk):
Mã thư viện được nhúng sẵn, đảm bảo ứng dụng luôn chạy mà không phụ thuộc vào việc tệp .so có tồn tại, có đúng phiên bản hay không. Điều này là tối quan trọng cho các chức năng an toàn (Ví dụ: hệ thống túi khí không thể lỗi vì không tìm thấy thư viện).

Tính Toàn vẹn (Immutability): 
Mã thư viện đã được xác thực, kiểm tra và ký số cùng với ứng dụng. Bất kỳ thay đổi nào bên ngoài (ví dụ: lỗi cập nhật, can thiệp bên ngoài) vào thư viện sẽ không ảnh hưởng đến tệp thực thi.

Tính Xác định (Deterministic Execution): 
Quá trình tải và khởi tạo ứng dụng đơn giản hơn, giảm thiểu các vấn đề phức tạp trong quá trình tải động (Dynamic Loading) có thể gây ra độ trễ hoặc lỗi không mong muốn.

   4) Khi nào dynamic có lợi hơn?  
      - Kịch bản: Cập nhật lỗ hổng bảo mật trong libFLAC mà không cần phải xác thực lại và triển khai toàn bộ ứng dụng âm nhạc (Music Application).

      Thực tế: Nếu có một lỗ hổng bảo mật nghiêm trọng (ví dụ: lỗi tràn bộ đệm) được phát hiện trong libFLAC.so (thư viện giải mã âm thanh), nhà sản xuất chỉ cần phát hành một bản cập nhật riêng lẻ cho tệp libFLAC.so đã được vá.

      Lợi ích:

      Kích thước bản vá nhỏ: Chỉ cần tải xuống một tệp .so nhỏ thay vì toàn bộ ứng dụng âm nhạc (có thể lên tới hàng chục, hàng trăm MB).

      Giảm thời gian cập nhật: Giảm thời gian chết của hệ thống.

      Xác thực đơn giản: Không cần phải lặp lại quy trình xác thực và kiểm thử nghiêm ngặt cho toàn bộ ứng dụng, chỉ cần kiểm tra khả năng tương thích của thư viện mới.

   5️) Viết lệnh biên dịch (g++)
    # Cách biên dịch với STATIC LINKING:
    g++ main.cpp -o player_static.exe libFLAC.a

    # Cách biên dịch với DYNAMIC LINKING:
    g++ main.cpp -o player_static.exe libFLAC.a

*/

/*
Fix : Giải pháp đề xuất: 

*/



int main() {
    std::cout << "Music Player Starting..." << std::endl;
    decodeFLAC(); // Gọi hàm từ libFLAC
    std::cout << "Music Player Finished!" << std::endl;
    return 0;
}

/* Đầu ra mong đợi khi chạy chương trình:
Music Player Starting...
[libFLAC] Decoding FLAC audio data...
Music Player Finished!

*/