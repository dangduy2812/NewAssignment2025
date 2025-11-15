#include <iostream>
#include <cstdlib>
#include "exercise/ex1.hpp"
#include "exercise/ex2.hpp"
#include "exercise/ex3.hpp"
#include "exercise/ex4.hpp"
using namespace std;


int main() {
    int choice;
    do {

        cout << "=== ASSIGNMENTS 11 ===\n";
        cout << "1. Exercise 1: Designing an Audio Source Interface with an Abstract Class\n";
        cout << "2. Exercise 2: Encapsulation and the friend Keyword for Hardware Control\n";
        cout << "3. Exercise 3: Applying the Abstract Factory Pattern for Audio Decoders\n";
        cout << "4. Exercise 4: Applying the Template Method Pattern for a Playlist Importer\n";
        cout << "0. Exit\n";
        cout << "==============================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls"); // dùng 'clear' nếu bạn chạy trên Linux/Mac

        switch (choice) {
        case 1:
            cout << "=== Exercise 1: Designing an Audio Source Interface with an Abstract Class ===\n\n";
            runExercise1();
            break;
        case 2:
            cout << "=== Exercise 2: Encapsulation and the friend Keyword for Hardware Control ===\n\n";
            runExercise2();
            break;
        case 3:
            cout << "=== Exercise 3: Applying the Abstract Factory Pattern for Audio Decoders ===\n\n";
            runExercise3();
            break;
        case 4:
            cout << "=== Exercise 4: Applying the Template Method Pattern for a Playlist Importer ===\n\n";
            runExercise4();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to return to the main menu...";
            cin.ignore();
            cin.get();
            system("cls");
        }

    } while (choice != 0);

    return 0;
}
