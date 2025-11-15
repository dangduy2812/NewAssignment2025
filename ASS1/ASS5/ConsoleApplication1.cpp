#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// ===================================================
//                 EXERCISE 1
// ===================================================
void Exercise1() {
    int option;
    int currentSong = 1;
    int songTime = 0;
    bool isRunning = true;

    do {
        system("cls");
        cout << "==============================\n";
        cout << "     EXERCISE 1: MEDIA PLAYER \n";
        cout << "==============================\n";
        cout << "1. Open Media Player screen\n";
        cout << "2. Switch to Navigation screen (simulate)\n";
        cout << "3. Back to Media Player\n";
        cout << "4. Next Song\n";
        cout << "0. Return to main menu\n";
        cout << "------------------------------\n";
        cout << "Choose option: ";
        cin >> option;

        switch (option) {
        case 1:
            system("cls");
            cout << "=== MEDIA PLAYER SCREEN ===\n";
            cout << "Now playing: Song #" << currentSong << "\n";
            cout << "Play time: " << songTime << " seconds\n";
            songTime += 3; // giả lập phát nhạc thêm 3 giây
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "=== NAVIGATION SCREEN ===\n";
            cout << "Switching to map screen...\n";
            cout << "(Media still playing in background)\n";
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "=== BACK TO MEDIA PLAYER ===\n";
            cout << "Resuming from Song #" << currentSong << " at " << songTime << "s\n";
            songTime += 3;
            system("pause");
            break;
        case 4:
            system("cls");
            currentSong++;
            songTime = 0; // reset thời gian khi đổi bài
            cout << "=== NEXT SONG ===\n";
            cout << "Now playing: Song #" << currentSong << "\n";
            system("pause");
            break;
        case 0:
            isRunning = false;
            cout << "Returning to main menu...\n";
            system("pause");
            break;
        default:
            cout << "Invalid choice!\n";
            system("pause");
        }
    } while (isRunning);
}


// ===================================================
//                 EXERCISE 2
// ===================================================
struct Song {
    string title;
    int duration;
};

class Playlist {
private:
    vector<Song> songs;
public:
    Playlist() {
        songs.push_back({ "Shape of You", 240 });
        songs.push_back({ "Blinding Lights", 200 });
        songs.push_back({ "Someone Like You", 250 });
    }
    void addSong(const string& title, int duration) {
        songs.push_back({ title, duration });
    }
    void showSongs() const {
        cout << "Playlist has " << songs.size() << " songs:\n";
        for (int i = 0; i < (int)songs.size(); ++i) {
            cout << i + 1 << ". " << songs[i].title << " (" << songs[i].duration << "s)\n";
        }
    }
};

// Truyền theo VALUE (copy toàn bộ)
void addSongByValue(Playlist playlist) {
    cout << "\n[Inside addSongByValue()] Adding new song...\n";
    playlist.addSong("Song (Pass by Value)", 180);
    playlist.showSongs();
}

// Truyền theo REFERENCE (tham chiếu trực tiếp)
void addSongByReference(Playlist& playlist) {
    cout << "\n[Inside addSongByReference()] Adding new song...\n";
    playlist.addSong("Song (Pass by Reference)", 210);
    playlist.showSongs();
}

void Exercise2() {
    Playlist playlist;
    char option;
    do {
        system("cls");
        cout << "========= EXERCISE 2 =========\n";
        cout << "Pass by Value vs Pass by Reference\n";
        cout << "---------------------------------\n";
        cout << "1. Show playlist\n";
        cout << "2. Add song (by VALUE)\n";
        cout << "3. Add song (by REFERENCE)\n";
        cout << "0. Return to main menu\n";
        cout << "---------------------------------\n";
        cout << "Choose option: ";
        cin >> option;

        switch (option) {
        case '1':
            system("cls");
            playlist.showSongs();
            system("pause");
            break;
        case '2':
            system("cls");
            cout << "Before adding:\n";
            playlist.showSongs();
            addSongByValue(playlist);
            cout << "\nAfter function returns (playlist real data):\n";
            playlist.showSongs();
            cout << "\n--> No change, because passed by VALUE.\n";
            system("pause");
            break;
        case '3':
            system("cls");
            cout << "Before adding:\n";
            playlist.showSongs();
            addSongByReference(playlist);
            cout << "\nAfter function returns (playlist real data):\n";
            playlist.showSongs();
            cout << "\n--> Changed, because passed by REFERENCE.\n";
            system("pause");
            break;
        }
    } while (option != '0');
}


// ===================================================
//                 EXERCISE 3
// ===================================================
// Pointer and Array Manipulation
void showArray(int* arr, int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << "\n";
}

void Exercise3() {
    system("cls");
    cout << "========= EXERCISE 3 =========\n";
    cout << "Pointer and Array Manipulation\n";
    cout << "------------------------------\n";

    int numbers[5] = { 10, 20, 30, 40, 50 };
    int* ptr = numbers;

    cout << "Original array: ";
    showArray(numbers, 5);

    cout << "Accessing elements using pointer arithmetic:\n";
    for (int i = 0; i < 5; i++) {
        cout << "*(ptr + " << i << ") = " << *(ptr + i) << "\n";
    }

    cout << "\nDoubling values using pointer...\n";
    for (int i = 0; i < 5; i++) {
        *(ptr + i) *= 2;
    }

    cout << "Array after modification: ";
    showArray(numbers, 5);

    system("pause");
}


// ===================================================
//                 EXERCISE 4
// ===================================================
// Structs and Object Composition
struct Engine {
    string type;
    int horsepower;
};

struct Car {
    string brand;
    Engine engine;
};

void Exercise4() {
    system("cls");
    cout << "========= EXERCISE 4 =========\n";
    cout << "Structs and Object Composition\n";
    cout << "------------------------------\n";

    Car car1 = { "Toyota", {"Hybrid", 120} };
    Car car2 = { "BMW", {"Petrol", 250} };

    cout << "Car 1: " << car1.brand << ", Engine: " << car1.engine.type
        << ", " << car1.engine.horsepower << " HP\n";
    cout << "Car 2: " << car2.brand << ", Engine: " << car2.engine.type
        << ", " << car2.engine.horsepower << " HP\n";

    system("pause");
}


// ===================================================
//                 EXERCISE 5
// ===================================================
// Basic File I/O Simulation (no real file, just console)
void Exercise5() {
    system("cls");
    cout << "========= EXERCISE 5 =========\n";
    cout << "File I/O Simulation (console-based)\n";
    cout << "----------------------------------\n";

    vector<string> lines;
    string input;

    cout << "Enter lines (type 'exit' to finish):\n";
    cin.ignore(); // clear buffer
    while (true) {
        getline(cin, input);
        if (input == "exit") break;
        lines.push_back(input);
    }

    cout << "\n=== Displaying Saved Content ===\n";
    for (const string& line : lines)
        cout << line << "\n";

    cout << "----------------------------------\n";
    cout << "(Simulated writing/reading file)\n";
    system("pause");
}


// ===================================================
//                 MAIN MENU
// ===================================================
int main() {
    char choice;
    do {
        system("cls");
        cout << "=========== MAIN MENU ===========\n";
        cout << "Assignment 1 - All Exercises\n";
        cout << "---------------------------------\n";
        cout << "1. Exercise 1 - Media Player\n";
        cout << "2. Exercise 2 - Pass by Value/Reference\n";
        cout << "3. Exercise 3 - Pointer & Array\n";
        cout << "4. Exercise 4 - Struct Composition\n";
        cout << "5. Exercise 5 - File I/O Simulation\n";
        cout << "0. Exit Program\n";
        cout << "---------------------------------\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case '1': Exercise1(); break;
        case '2': Exercise2(); break;
        case '3': Exercise3(); break;
        case '4': Exercise4(); break;
        case '5': Exercise5(); break;
        case '0': cout << "Exiting program...\n"; system("pause"); break;
        default: cout << "Invalid choice!\n"; system("pause");
        }
    } while (choice != '0');

    return 0;
}
