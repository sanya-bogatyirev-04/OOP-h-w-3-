#ifndef MODEM_H
#define MODEM_H

#include <string>
#include <iostream>
#include "colors.h"

class Modem {
public:
    enum ConnectionType { DSL, CABLE, FIBER, SATELLITE };
    enum Protocol { PPP, SLIP, PPTP, L2TP };

    Modem();
    Modem(const std::string& manufacturer, const std::string& model,
          const std::string& serialNumber, ConnectionType connection,
          Protocol protocol, double price, bool wifiSupport,
          int maxSpeed, int portsCount);

    std::string getManufacturer() const { return manufacturer; }
    std::string getModel() const { return model; }
    std::string getSerialNumber() const { return serialNumber; }
    ConnectionType getConnection() const { return connection; }
    Protocol getProtocol() const { return protocol; }
    double getPrice() const { return price; }
    bool hasWifiSupport() const { return wifiSupport; }
    int getMaxSpeed() const { return maxSpeed; }
    int getPortsCount() const { return portsCount; }

    void setManufacturer(const std::string& newManufacturer) { manufacturer = newManufacturer; }
    void setModel(const std::string& newModel) { model = newModel; }
    void setSerialNumber(const std::string& newSerialNumber) { serialNumber = newSerialNumber; }
    void setConnection(ConnectionType newConnection) { connection = newConnection; }
    void setProtocol(Protocol newProtocol) { protocol = newProtocol; }
    void setPrice(double newPrice) { price = newPrice; }
    void setWifiSupport(bool hasWifiSupport) { wifiSupport = hasWifiSupport; }
    void setMaxSpeed(int newMaxSpeed) { maxSpeed = newMaxSpeed; }
    void setPortsCount(int count) { portsCount = count; }

    void displayInfo(const Modem* original = nullptr) const;
    void serialize(std::ostream& os) const;
    bool deserialize(std::istream& is);

private:
    std::string manufacturer;
    std::string model;
    std::string serialNumber;
    ConnectionType connection;
    Protocol protocol;
    double price;
    bool wifiSupport;
    int maxSpeed;
    int portsCount;
};

#endif // MODEM_H
