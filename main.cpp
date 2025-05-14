#include "menu.h"
#include "database.h"
#include <iostream>
#include <windows.h>
#include <limits>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Database db;
    Menu menu(db);

    std::cout << "=== Программа учета модемов ===" << std::endl;
    std::cout << "Автор: Богатырев Александр\n";
    std::cout << "Группа: ИЦТМС 2-6\n";
    std::cout << "Вариант: Модем\n";

    int choice;
    do {
        menu.showMainMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice != 0) {
            menu.processMainMenu(choice);
        }
    } while (choice != 0);

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.get();
    return 0;
}
