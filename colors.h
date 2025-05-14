#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <windows.h>
#include <string>

inline void highlightChanged(const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << text;
        SetConsoleTextAttribute(hConsole, 7);
    } else {
        std::cout << text;
    }
}

#endif // COLORS_H
