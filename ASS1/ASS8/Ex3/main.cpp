#include <iostream>
#include <string>

/* PHÂN TÍCH
TÌNH HUỐNG:
Hàm selectNextInPlaylist_WRONG(Song* current) nhận con trỏ theo giá trị (pass by value).
Khi thay đổi 'current' bên trong hàm, chỉ có bản sao cục bộ bị thay đổi, con trỏ gốc
trong hàm gọi (nowPlaying) không bị ảnh hưởng.

YÊU CẦU:
1. Phân tích: Sự khác biệt giữa Song* p (truyền giá trị), Song*& p (tham chiếu đến con trỏ),
   và Song** p (con trỏ đến con trỏ). (Đã giải thích chi tiết trong comment).
2. Sửa lỗi: Viết lại hàm bằng Song*& và Song**.


SỰ KHÁC BIỆT GIỮA CÁC CÁCH TRUYỀN CON TRỎ
1. Song* p (Truyền Giá trị - Pass by Value):
   - Chức năng: Cho phép thay đổi dữ liệu mà con trỏ TỚI (bằng *p).
   - KHÔNG cho phép: Thay đổi bản thân con trỏ p (địa chỉ nó lưu trữ) bên ngoài hàm gọi.
   - Cơ chế: p là một bản sao cục bộ, nằm trên Stack của hàm được gọi.
   
2. Song*& p (Tham chiếu đến Con trỏ - Reference to Pointer):
   - Chức năng: Cho phép thay đổi dữ liệu mà con trỏ TỚI (*p) VÀ thay đổi bản thân con trỏ p.
   - Cơ chế: p là một bí danh (alias) của con trỏ gốc (nowPlaying). Mọi thao tác với p đều trực tiếp thao tác lên nowPlaying.
   
3. Song** p (Con trỏ đến Con trỏ - Pointer to Pointer):
   - Chức năng: Cho phép thay đổi dữ liệu mà con trỏ TỚI (*p) VÀ thay đổi bản thân con trỏ gốc (thông qua **p).
   - Cơ chế: p lưu trữ địa chỉ của con trỏ gốc. Để thay đổi con trỏ gốc, ta phải dùng hủy tham chiếu một lần (*p).

   
*/

struct Song {
    std::string title;
    Song* next; // Con tro toi bai hat tiep theo
};

// Hàm tiện ích để in trạng thái con trỏ
void printStatus(const std::string& label, Song* p) {
    if (p) {
        std::cout << label << " tro den: " << p->title << std::endl;
    } else {
        std::cout << label << " tro den: NULL" << std::endl;
    }
}

// LỖI: Hàm này chỉ thay đổi bản sao cục bộ của con trỏ
void selectNextInPlaylist_WRONG(Song* current) {
    if (current != nullptr && current->next != nullptr) {
        // Chi thay doi ban sao cuc bo
        current = current->next; 
    }
}

// -----------------------------------------------------------------
// SỬA LỖI - PHƯƠNG PHÁP 1: Tham chiếu đến Con trỏ (Song*&)
// 'current' là bí danh của con trỏ gốc. Thay đổi 'current' thay đổi con trỏ gốc.
void selectNextInPlaylist_Ref(Song*& current) {
    if (current != nullptr && current->next != nullptr) {
        // Thay đổi giá trị của con trỏ gốc
        current = current->next; 
    }
}

// -----------------------------------------------------------------
// SỬA LỖI - PHƯƠNG PHÁP 2: Con trỏ đến Con trỏ (Song**)
// 'currentPtr' luu dia chi cua con tro Song* goc. Phai dung *currentPtr de thay doi con tro goc.
void selectNextInPlaylist_PtrPtr(Song** currentPtr) {
    // current luu gia tri (dia chi) cua con tro goc
    Song* current = *currentPtr; 
    
    if (current != nullptr && current->next != nullptr) {
        // Thay doi con tro goc (*currentPtr) de tro den next
        *currentPtr = current->next; 
    }
}

int main() {
    // 1. Khởi tạo danh sách liên kết đơn: A -> B -> C -> NULL
    Song songC = {"Song C", nullptr};
    Song songB = {"Song B", &songC};
    Song songA = {"Song A", &songB};

    // -----------------------------------------------------------------
    
    std::cout << "--- MINH HOA LOI GOC ---" << std::endl;
    Song* nowPlaying_WRONG = &songA; 
    printStatus("1. Truoc WRONG", nowPlaying_WRONG);

    // Goi ham sai (truyen theo gia tri)
    selectNextInPlaylist_WRONG(nowPlaying_WRONG);

    printStatus("2. Sau WRONG", nowPlaying_WRONG);
    std::cout << "Ket qua: Con tro goc KHONG THAY DOI." << std::endl;
    
    // -----------------------------------------------------------------
    
    std::cout << "\n--- PHUONG PHAP 1: Reference to Pointer (Song*&) ---" << std::endl;
    Song* nowPlaying_REF = &songA; 
    printStatus("3. Truoc REF", nowPlaying_REF);

    // Goi ham dung (Truyen tham chieu toi con tro)
    selectNextInPlaylist_Ref(nowPlaying_REF); // Ham nhan Song*&

    printStatus("4. Sau REF", nowPlaying_REF);
    
    // Di chuyen tiep len Song C
    selectNextInPlaylist_Ref(nowPlaying_REF);
    printStatus("5. Sau REF lan 2", nowPlaying_REF);
    
    // -----------------------------------------------------------------
    
    std::cout << "\n--- PHUONG PHAP 2: Pointer to Pointer (Song**) ---" << std::endl;
    Song* nowPlaying_PTRPTR = &songA; 
    printStatus("6. Truoc PTRPTR", nowPlaying_PTRPTR);

    // Goi ham dung (Truyen DIA CHI (&) cua con tro)
    selectNextInPlaylist_PtrPtr(&nowPlaying_PTRPTR); // Ham nhan Song**

    printStatus("7. Sau PTRPTR", nowPlaying_PTRPTR);
    
    // Di chuyen tiep len Song C
    selectNextInPlaylist_PtrPtr(&nowPlaying_PTRPTR);
    printStatus("8. Sau PTRPTR lan 2", nowPlaying_PTRPTR);

    return 0;
}