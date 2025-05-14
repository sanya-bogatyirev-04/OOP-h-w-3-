#include "database.h"
#include <iostream>
#include <fstream>

Database::Database() : head(nullptr), tail(nullptr), size(0) {}

Database::~Database() {
    clear();
}

void Database::add(const Modem& md) {
    Node* newNode = new Node(md);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

bool Database::remove(const std::string& manufacturer, const std::string& model) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.getManufacturer() == manufacturer &&
            current->data.getModel() == model) {

            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;

            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;

            delete current;
            size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool Database::edit(const std::string& manufacturer, const std::string& model, const Modem& newData) {
    Node* node = find(manufacturer, model);
    if (node) {
        node->data = newData;
        return true;
    }
    return false;
}

Node* Database::find(const std::string& manufacturer, const std::string& model) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.getManufacturer() == manufacturer &&
            current->data.getModel() == model) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Database::displayAll() const {
    Node* current = head;
    while (current != nullptr) {
        current->data.displayInfo();
        std::cout << std::endl;
        current = current->next;
    }
}

bool Database::isEmpty() const {
    return size == 0;
}

int Database::getSize() const {
    return size;
}

bool Database::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    clear();

    Modem modem;
    while (modem.deserialize(file)) {
        add(modem);
    }

    file.close();
    return !isEmpty();
}

bool Database::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    Node* current = head;
    while (current != nullptr) {
        current->data.serialize(file);
        current = current->next;
    }

    file.close();
    return true;
}

void Database::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}
