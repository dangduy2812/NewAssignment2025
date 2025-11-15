#include <iostream>
#include <cstdlib> // system("cls"), system("pause")

#include "exercise/ex1.hpp"
#include "exercise/ex2.hpp"
#include "exercise/ex3.hpp"
#include "exercise/ex4.hpp"

int main() {
    int choice;
    do {
        system("cls");
        std::cout << "=== ASSIGNMENTS MENU ===\n";
        std::cout << "1. Bai 1: Pass-by-Value vs Pass-by-Reference\n";
        std::cout << "2. Bai 2: Flexible API with Default Arguments\n";
        std::cout << "3. Bai 3: Function Overloading for Playlist Searches\n";
        std::cout << "4. Bai 4: Passing Pointers vs Modifying Pointer Data\n";
        std::cout << "0. Thoat\n";
        std::cout << "Chon: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                RunEx1();
                break;
            case 2:
                RunEx2();
                break;
            case 3:
                RunEx3();
                break;
            case 4:
                RunEx4();
                break;
            case 0:
                std::cout << "Thoat chuong trinh.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le!\n";
                system("pause");
        }
    } while(choice != 0);

    return 0;
}
