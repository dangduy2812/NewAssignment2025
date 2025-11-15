#include <iostream>
#include <cstdlib>
#include "exercise/ex1.hpp"
#include "exercise/ex2.hpp"
#include "exercise/ex3.hpp"
#include "exercise/ex4.hpp"

using namespace std;

int main() {
    int choice = 0;

    do {
        system("cls"); // xóa màn hình
        cout << "===== OOP Advanced Exercises =====\n";
        cout << "1. Exercise 1 - Diamond Problem\n";
        cout << "2. Exercise 2 - Method Overriding & Access Level\n";
        cout << "3. Exercise 3 - Constructor/Destructor & Virtual Destructor\n";
        cout << "4. Exercise 4 - Object Slicing\n";
        cout << "0. Exit\n";
        cout << "Select exercise: ";
        cin >> choice;

        system("cls"); // xóa màn hình trước khi chạy exercise
        switch(choice) {
            case 1:
                runExercise1();
                break;
            case 2:
                runExercise2();
                break;
            case 3:
                runExercise3();
                break;
            case 4:
                runExercise4();
                break;
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
        if (choice != 0) {
            cout << "\n";
            system("pause"); // tạm dừng để xem kết quả
        }
    } while (choice != 0);

    return 0;
}