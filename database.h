#ifndef DATABASE_H
#define DATABASE_H

#include "modem.h"
#include <string>
#include <fstream>

class Node {
public:
    Modem data;
    Node* prev;
    Node* next;

    explicit Node(const Modem& md) : data(md), prev(nullptr), next(nullptr) {}
};

class Database {
public:
    Database();
    ~Database();

    void add(const Modem& md);
    bool remove(const std::string& manufacturer, const std::string& model);
    bool edit(const std::string& manufacturer, const std::string& model, const Modem& newData);
    Node* find(const std::string& manufacturer, const std::string& model) const;
    void displayAll() const;
    bool isEmpty() const;
    int getSize() const;

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;

private:
    void clear();
    Node* head;
    Node* tail;
    int size;

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
};

#endif // DATABASE_H
