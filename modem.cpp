#include "modem.h"
#include <limits>

Modem::Modem() :
    manufacturer("Unknown"), model("Unknown"), serialNumber(""),
    connection(DSL), protocol(PPP), price(0.0),
    wifiSupport(false), maxSpeed(0), portsCount(1) {}

Modem::Modem(const std::string& manufacturer, const std::string& model,
             const std::string& serialNumber, ConnectionType connection,
             Protocol protocol, double price, bool wifiSupport,
             int maxSpeed, int portsCount) :
    manufacturer(manufacturer), model(model), serialNumber(serialNumber),
    connection(connection), protocol(protocol), price(price),
    wifiSupport(wifiSupport), maxSpeed(maxSpeed), portsCount(portsCount) {}

void Modem::displayInfo(const Modem* original) const {
    auto printField = [&](const std::string& name, const auto& value, auto Modem::*member) {
        std::cout << name << ": ";
        if (original && (this->*member != original->*member)) {
            highlightChanged(std::to_string(value));
        } else {
            std::cout << value;
        }
        std::cout << std::endl;
    };

    auto printStrField = [&](const std::string& name, const std::string& value, auto Modem::*member) {
        std::cout << name << ": ";
        if (original && (this->*member != original->*member)) {
            highlightChanged(value);
        } else {
            std::cout << value;
        }
        std::cout << std::endl;
    };

    std::cout << "=== Модем ===" << std::endl;
    printStrField("Производитель", manufacturer, &Modem::manufacturer);
    printStrField("Модель", model, &Modem::model);
    printStrField("Серийный номер", serialNumber, &Modem::serialNumber);

    std::cout << "Тип подключения: ";
    if (original && connection != original->connection) {
        highlightChanged("");
        switch (connection) {
        case DSL: std::cout << "DSL"; break;
        case CABLE: std::cout << "Cable"; break;
        case FIBER: std::cout << "Fiber"; break;
        case SATELLITE: std::cout << "Satellite"; break;
        }
    } else {
        switch (connection) {
        case DSL: std::cout << "DSL"; break;
        case CABLE: std::cout << "Cable"; break;
        case FIBER: std::cout << "Fiber"; break;
        case SATELLITE: std::cout << "Satellite"; break;
        }
    }
    std::cout << std::endl;

    std::cout << "Протокол: ";
    if (original && protocol != original->protocol) {
        highlightChanged("");
        switch (protocol) {
        case PPP: std::cout << "PPP"; break;
        case SLIP: std::cout << "SLIP"; break;
        case PPTP: std::cout << "PPTP"; break;
        case L2TP: std::cout << "L2TP"; break;
        }
    } else {
        switch (protocol) {
        case PPP: std::cout << "PPP"; break;
        case SLIP: std::cout << "SLIP"; break;
        case PPTP: std::cout << "PPTP"; break;
        case L2TP: std::cout << "L2TP"; break;
        }
    }
    std::cout << std::endl;

    printField("Цена", price, &Modem::price);
    std::cout << "Wi-Fi: ";
    if (original && wifiSupport != original->wifiSupport) {
        highlightChanged(wifiSupport ? "Да" : "Нет");
    } else {
        std::cout << (wifiSupport ? "Да" : "Нет");
    }
    std::cout << std::endl;

    printField("Макс. скорость (Мбит/с)", maxSpeed, &Modem::maxSpeed);
    printField("Количество портов", portsCount, &Modem::portsCount);
}

void Modem::serialize(std::ostream& os) const {
    os << manufacturer << '\n'
       << model << '\n'
       << serialNumber << '\n'
       << static_cast<int>(connection) << '\n'
       << static_cast<int>(protocol) << '\n'
       << price << '\n'
       << wifiSupport << '\n'
       << maxSpeed << '\n'
       << portsCount << '\n';
}

bool Modem::deserialize(std::istream& is) {
    int conn, proto;
    if (!(std::getline(is, manufacturer) &&
          std::getline(is, model) &&
          std::getline(is, serialNumber) &&
          (is >> conn >> proto >> price >> wifiSupport >> maxSpeed >> portsCount))) {
        return false;
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    connection = static_cast<ConnectionType>(conn);
    protocol = static_cast<Protocol>(proto);
    return true;
}
