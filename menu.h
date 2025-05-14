#ifndef MENU_H
#define MENU_H

#include "database.h"
#include <string>

class Menu {
public:
    explicit Menu(Database& database) : db(database) {}

    void showMainMenu() const;
    void showAddMenu() const;
    void showRemoveMenu() const;
    void showEditMenu() const;
    void showFindMenu() const;
    void showFileMenu() const;

    void processMainMenu(int choice);
    void processFileMenu(int choice);

private:
    Modem inputModem() const;
    void inputManufacturerAndModel(std::string& manufacturer, std::string& model) const;
    Database& db;
};

#endif // MENU_H
