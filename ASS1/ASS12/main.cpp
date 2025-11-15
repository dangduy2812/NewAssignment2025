#include <iostream>
#include <cstdlib>
#include "exercise/ex1.hpp"
#include "exercise/ex2.hpp"
#include "exercise/ex3.hpp"
#include "exercise/ex4.hpp"

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

int main() {
    int choice = 0;
    do {
        clearScreen();
        cout << "===== MENU CHON EXERCISE =====\n";
        cout << "1. Exercise 1: Audio Source Interface (Abstract Class)\n";
        cout << "2. Exercise 2: CarAudioSystem & friend\n";
        cout << "3. Exercise 3: Abstract Factory Audio Decoder\n";
        cout << "4. Exercise 4: Playlist Importer (Template Method)\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";
        cin >> choice;
        cin.ignore(); // bo ky tu '\n'

        clearScreen();
        switch(choice) {
            case 1:
                cout << "===== EXERCISE 1 =====\n";
                runExercise1();
                pauseScreen();
                break;
            case 2:
                cout << "===== EXERCISE 2 =====\n";
                runExercise2();
                pauseScreen();
                break;
            case 3:
                cout << "===== EXERCISE 3 =====\n";
                runExercise3();
                pauseScreen();
                break;
            case 4:
                cout << "===== EXERCISE 4 =====\n";
                runExercise4();
                pauseScreen();
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                pauseScreen();
                break;
        }
    } while(choice != 0);

    return 0;
}
