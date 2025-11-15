#include <iostream>
#include <vector>
#include <string>
#include <list> // Thêm thư viện list cho Giải pháp 2

/* PHÂN TÍCH
Viết lại tình huống, và yêu cầu
Tình huống:
Ứng dụng quản lý playlist bằng std::vector<Song>. Lấy một con trỏ (Song*)
đến bài hát hiện tại (currentSongPtr). Sau đó, thêm các bài hát mới vào vector.

Vấn đề:
Việc thêm (push_back) có thể làm vector thay đổi dung lượng (reallocate).
Nếu reallocate xảy ra, vector sẽ di chuyển toàn bộ dữ liệu sang một vùng bộ nhớ mới.
Khi đó, 'currentSongPtr' ban đầu sẽ trỏ đến vùng bộ nhớ cũ đã bị giải phóng hoặc
chứa dữ liệu không liên quan, trở thành một Dangling Pointer Truy cập nó
sẽ gây ra Lỗi Không Xác Định (Undefined Behavior) hoặc crash chương trình.
*/

struct Song {
    std::string title;
};

// --- Bắt đầu phần FIX (Giải quyết và Trả lời các câu hỏi) ---

/*
FIX - Trả lời câu hỏi 1:
Analyze the Bug: Giải thích chi tiết tại sao currentSongPtr trở nên không hợp lệ.
Mô tả cơ chế cấp phát lại bộ nhớ (reallocation) của std::vector.

Trả lời:
std::vector quản lý các phần tử trong một khối bộ nhớ liên tục. Khi bạn thêm
một phần tử mới (push_back) và dung lượng hiện tại (capacity) không đủ,
vector sẽ thực hiện reallocation:
1. Nó cấp phát một khối bộ nhớ mới, lớn hơn (thường là gấp đôi dung lượng cũ).
2. Nó sao chép (hoặc di chuyển) tất cả các phần tử hiện có từ vùng bộ nhớ cũ sang vùng bộ nhớ mới.
3. Nó giải phóng vùng bộ nhớ cũ.

Do 'currentSongPtr' trỏ đến địa chỉ của 'Song A' trong vùng bộ nhớ cũ, nên sau
khi vector reallocate, địa chỉ này không còn hợp lệ nữa (nó đã bị giải phóng hoặc
được sử dụng cho mục đích khác). Do đó, 'currentSongPtr' trở thành một Dangling Pointer
*/

void run_dangling_pointer_example() {
    std::cout << "--- Vi du Loi Dangling Pointer ---" << std::endl;
    std::vector<Song> playlist = {{"Song A"}, {"Song B"}};
    int currentIndex = 0;

    // In ra địa chỉ ban đầu của vector và Song A
    std::cout << "Dai chi (playlist.data()): " << playlist.data() << std::endl;
    std::cout << "Dung luong ban dau (capacity): " << playlist.capacity() << std::endl;

    // 1. Lấy một con trỏ đến bài hát hiện tại
    Song* currentSongPtr = &playlist[currentIndex];
    std::cout << "1. Dia chi của Song A: " << (void*)currentSongPtr << std::endl;
    std::cout << "   truoc reallocate: " << currentSongPtr->title << std::endl;

    // 2. Thêm nhiều bài hát, gây ra reallocate nếu capacity không đủ
    // Để đảm bảo reallocate xảy ra, ta thêm nhiều hơn capacity - size
    std::cout << "\n2. them bai hat... (Co the gay Reallocate!)" << std::endl;
    
    // Nếu capacity ban đầu là 2, thì 2 push_back tiếp theo sẽ gây reallocate.
    // Nếu capacity ban đầu lớn hơn 2, ta cần thêm nhiều hơn.
    playlist.push_back({"Song C"});
    playlist.push_back({"Song D"});
    playlist.push_back({"Song E"}); // Chắc chắn gây reallocate trong nhiều trường hợp
    
    // In ra địa chỉ mới sau khi thêm
    std::cout << "  Dia chi moi (playlist.data()): " << playlist.data() << std::endl;
    std::cout << "   Dung luong moi (capacity): " << playlist.capacity() << std::endl;


    // 3. VẤN ĐỀ: currentSongPtr có thể không hợp lệ do địa chỉ đã thay đổi.
    std::cout << "\n3. Thu truy cap bang con tro cu..." << std::endl;
    std::cout << "   Dia chi cua Song A (Con tro cu): " << (void*)currentSongPtr << std::endl;
    // Việc truy cập này là Undefined Behavior.
    // Kết quả có thể là: in ra Song A (nếu không reallocate, hoặc reallocate nhưng vùng nhớ
    // cũ chưa bị ghi đè), in ra rác, hoặc chương trình crash.
    std::cout << "Sau reallocate (su dung con tro cu): " << currentSongPtr->title << std::endl; 
    std::cout << "NOte: Dong trtn gay loi Dangling Pointer/Undefined Behavior!" << std::endl;
}

// 
/*
FIX - Trả lời câu hỏi 2:
Propose Safe Solutions: Trình bày ít nhất hai chiến lược an toàn.

Method 1 (Use an Index): Thay vì lưu con trỏ thô, lưu chỉ mục (index) của bài hát.
Giải thích 
Vấn đề cũ với con trỏ:
Nếu lưu Song* currentSongPtr = &playlist[0];
Khi push_back gây reallocate, con trỏ trở thành dangling pointer -> UB.
Giải pháp dùng index:
currentIndex = 0 lưu vị trí trong vector, không phụ thuộc vào địa chỉ vật lý.
Sau push_back hoặc reallocate, truy cập playlist[currentIndex] luôn đúng.
Ưu điểm:
An toàn, không cần biết vector có reallocate hay không.
Mã dễ đọc và dễ bảo trì.
*/
void safe_solution_index() {
    std::cout << "\n--- Giai Phap 1: Su dung chi muc (Index) ---" << std::endl;

    // Tạo vector playlist ban đầu với 2 bài hát
    std::vector<Song> playlist = {{"Song A"}, {"Song B"}};
    
    // Lưu chỉ mục thay vì con trỏ
    int currentIndex = 0; 
    // currentIndex trỏ đến bài hát đầu tiên trong playlist (Song A)

    // Lấy tham chiếu đến bài hát hiện tại
    Song& currentSongRef = playlist[currentIndex];
    std::cout << "Bai hat hien tai: " << currentSongRef.title << std::endl;

    // Thêm các bài hát mới (có thể gây reallocate)
    std::cout << "Them bai hat moi..." << std::endl;
    playlist.push_back({"Song C"});
    playlist.push_back({"Song D"});
    playlist.push_back({"Song E"}); 

    // Nếu vector phải cấp phát lại bộ nhớ, tất cả con trỏ cũ sẽ bị invalid
    // Nhưng chỉ số currentIndex vẫn hợp lệ, vì chúng ta truy cập theo vị trí

    // Truy cập bài hát hiện tại bằng chỉ mục sau khi reallocate
    Song& newCurrentSongRef = playlist[currentIndex];
    std::cout << "Sau reallocate (Su dung Index): " << newCurrentSongRef.title << std::endl;

    // => AN TOÀN vì ta luôn tìm đến địa chỉ mới bằng index."  
    // Lưu ý: reference mới trỏ đến vị trí 0 trong vector hiện tại
}

/*
Method 2 (Use a Different Container): Sử dụng std::list. Giải thích tại sao std::list an toàn hơn (thêm/xóa không làm mất hiệu lực con trỏ/iterator của các phần tử khác).
*/
void safe_solution_list() {
    std::cout << "\n--- Giai Phap 2: Su dung std::list ---" << std::endl;
    /*std::list là danh sách liên kết đôi (doubly linked list).
Mỗi phần tử (Node) chứa:
- Dữ liệu (Song)
- Con trỏ đến phần tử trước (prev)
- Con trỏ đến phần tử sau (next)
Memory layout: mỗi phần tử được cấp phát riêng lẻ trên heap.
Tại sao an toàn với con trỏ/iterator
+-----------------+
| Song data       |
+-----------------+
| prev pointer    |
+-----------------+
| next pointer    |
+-----------------+
Bộ nhớ của node
Mỗi node được cấp phát riêng lẻ trên heap (dynamic memory).
Không đảm bảo liền kề nhau như std::vector.
Node tiếp theo/ trước được liên kết bằng con trỏ (next / prev) -> danh sách liên kết.

a) Thêm phần tử
Khi thêm phần tử mới (push_back, insert), std::list chỉ:
Cấp phát một node mới.
Liên kết node mới với các node lân cận.
Không di chuyển các node cũ → con trỏ/iterator đến các phần tử cũ vẫn hợp lệ.
b) Xóa phần tử
Khi xóa một phần tử, chỉ node đó bị giải phóng.
Con trỏ/iterator đến các node khác vẫn hợp lệ.
*/
    std::list<Song> playlist = {{"Song A"}, {"Song B"}};

    // Lấy iterator (hoặc con trỏ nếu dùng list<T*>) đến bài hát hiện tại.
    // Đối với std::list, iterator trỏ đến phần tử (node) chứ không phải vị trí
    // bộ nhớ liên tục.
    std::list<Song>::iterator currentSongIt = playlist.begin();
    std::cout << "Bai hat hien tai: " << currentSongIt->title << std::endl;

    // Thêm các bài hát mới vào cuối list.
    // Việc thêm vào std::list chỉ tạo một node mới và cập nhật con trỏ
    // của node cuối cùng. Nó không di chuyển các node đã tồn tại.
    std::cout << "Thêm bài hát mới..." << std::endl;
    playlist.push_back({"Song C"});
    playlist.push_back({"Song D"});
    playlist.push_back({"Song E"}); 

    // Truy cập bài hát hiện tại bằng iterator cũ.
    // Iterator/Pointer đến các phần tử *khác* không bị mất hiệu lực.
}


int main() {
    // Chạy ví dụ minh họa lỗi
    run_dangling_pointer_example();

    std::cout << "\n==========================================" << std::endl;

    // Chạy giải pháp 1
    safe_solution_index();

    std::cout << "\n==========================================" << std::endl;

    // Chạy giải pháp 2
    safe_solution_list();

    return 0;
}