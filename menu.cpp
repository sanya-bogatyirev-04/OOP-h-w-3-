#include "menu.h"
#include <iostream>
#include <limits>
#include <string>

void Menu::showMainMenu() const {
    std::cout << "\n=== Учет модемов ===" << std::endl;
    std::cout << "1. Просмотреть все" << std::endl;
    std::cout << "2. Добавить" << std::endl;
    std::cout << "3. Удалить" << std::endl;
    std::cout << "4. Редактировать" << std::endl;
    std::cout << "5. Поиск" << std::endl;
    std::cout << "6. Файлы" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите: ";
}

void Menu::showAddMenu() const {
    std::cout << "\n=== Добавление модема ===" << std::endl;
}

void Menu::showRemoveMenu() const {
    std::cout << "\n=== Удаление модема ===" << std::endl;
}

void Menu::showEditMenu() const {
    std::cout << "\n=== Редактирование модема ===" << std::endl;
}

void Menu::showFindMenu() const {
    std::cout << "\n=== Поиск модема ===" << std::endl;
}

void Menu::showFileMenu() const {
    std::cout << "\n=== Работа с файлами ===" << std::endl;
    std::cout << "1. Загрузить из файла" << std::endl;
    std::cout << "2. Сохранить в файл" << std::endl;
    std::cout << "0. Назад" << std::endl;
    std::cout << "Выберите: ";
}

void Menu::processMainMenu(int choice) {
    switch (choice) {
    case 1:
        if (db.isEmpty()) {
            std::cout << "База данных пуста!\n";
        } else {
            db.displayAll();
        }
        break;
    case 2:
        showAddMenu();
        db.add(inputModem());
        std::cout << "Модем успешно добавлен!\n";
        break;
    case 3: {
        showRemoveMenu();
        std::string manufacturer, model;
        inputManufacturerAndModel(manufacturer, model);
        if (db.remove(manufacturer, model)) {
            std::cout << "Модем успешно удален!\n";
        } else {
            std::cout << "Модем не найден!\n";
        }
        break;
    }
    case 4: {
        showEditMenu();
        std::string manufacturer, model;
        inputManufacturerAndModel(manufacturer, model);
        Node* found = db.find(manufacturer, model);
        if (found) {
            Modem newData = inputModem();
            found->data.displayInfo(&newData);
            if (db.edit(manufacturer, model, newData)) {
                std::cout << "Модем успешно изменен!\n";
            }
        } else {
            std::cout << "Модем не найден!\n";
        }
        break;
    }
    case 5: {
        showFindMenu();
        std::string manufacturer, model;
        inputManufacturerAndModel(manufacturer, model);
        Node* found = db.find(manufacturer, model);
        if (found) {
            std::cout << "Найден модем:\n";
            found->data.displayInfo();
        } else {
            std::cout << "Модем не найден!\n";
        }
        break;
    }
    case 6: {
        int fileChoice;
        do {
            showFileMenu();
            std::cin >> fileChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (fileChoice != 0) {
                processFileMenu(fileChoice);
            }
        } while (fileChoice != 0);
        break;
    }
    case 0:
        std::cout << "Выход из программы.\n";
        break;
    default:
        std::cout << "Неверный выбор. Попробуйте снова.\n";
    }
}

void Menu::processFileMenu(int choice) {
    const std::string filename = "modem.txt";

    switch (choice) {
    case 1:
        if (db.loadFromFile(filename)) {
            std::cout << "Данные успешно загружены!\n";
        } else {
            std::cout << "Ошибка загрузки данных!\n";
        }
        break;
    case 2:
        if (db.saveToFile(filename)) {
            std::cout << "Данные успешно сохранены!\n";
        } else {
            std::cout << "Ошибка сохранения данных!\n";
        }
        break;
    case 0:
        break;
    default:
        std::cout << "Неверный выбор. Попробуйте снова.\n";
    }
}

Modem Menu::inputModem() const {
    std::string manufacturer, model, serialNumber;
    double price;
    bool wifiSupport;
    int maxSpeed, portsCount;
    int connType, protoType;

    std::cout << "Производитель: ";
    std::getline(std::cin, manufacturer);

    std::cout << "Модель: ";
    std::getline(std::cin, model);

    do {
        std::cout << "Серийный номер: ";
        std::getline(std::cin, serialNumber);
    } while (serialNumber.empty());

    do {
        std::cout << "Тип подключения (0-DSL, 1-Cable, 2-Fiber, 3-Satellite): ";
        std::cin >> connType;
    } while (connType < 0 || connType > 3);

    do {
        std::cout << "Протокол (0-PPP, 1-SLIP, 2-PPTP, 3-L2TP): ";
        std::cin >> protoType;
    } while (protoType < 0 || protoType > 3);

    do {
        std::cout << "Цена: ";
        std::cin >> price;
    } while (price <= 0);

    std::cout << "Wi-Fi (0-Нет, 1-Да): ";
    std::cin >> wifiSupport;

    do {
        std::cout << "Макс. скорость (Мбит/с): ";
        std::cin >> maxSpeed;
    } while (maxSpeed <= 0);

    do {
        std::cout << "Количество портов: ";
        std::cin >> portsCount;
    } while (portsCount <= 0);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return Modem(manufacturer, model, serialNumber,
                 static_cast<Modem::ConnectionType>(connType),
                 static_cast<Modem::Protocol>(protoType),
                 price, wifiSupport, maxSpeed, portsCount);
}

void Menu::inputManufacturerAndModel(std::string& manufacturer, std::string& model) const {
    std::cout << "Производитель: ";
    std::getline(std::cin, manufacturer);

    std::cout << "Модель: ";
    std::getline(std::cin, model);
}
