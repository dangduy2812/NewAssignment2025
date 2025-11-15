#include <iostream>
#include "ex1.hpp"
#include "ex2.hpp"
#include "ex3.hpp"
#include "ex4.hpp"
using namespace std;

int main() {
    int choice;
    do {
        system("cls");
        cout << "===== MENU CHON BAI EXERCISE =====\n";
        cout << "1. Exercise 1: Binary Configuration Data\n";
        cout << "2. Exercise 2: Text-Based Playlist Parsing\n";
        cout << "3. Exercise 3: Chunk Audio File\n";
        cout << "4. Exercise 4: Safe Save Playlist\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Chon: ";
        cin >> choice;
        system("cls");

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
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                system("pause");
        }
    } while (choice != 0);

    return 0;
}
