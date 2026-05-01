// ============================================================
//  Vehicle.cpp
//  DEVELOPED BY: Reba Fatima Fawad (25L-2016) - Team Lead
//  Responsibility: Vehicle entity + encapsulated data
// ============================================================

#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

using namespace std;

// ---- Constructors ----
Vehicle::Vehicle() : entryTime(0), exitTime(0) {}

Vehicle::Vehicle(const string& vNum, const string& vType)
    : vehicleNumber(vNum), vehicleType(vType), entryTime(0), exitTime(0) {
}

// ---- Setters ----
void Vehicle::setVehicleNumber(const string& vNum) { vehicleNumber = vNum; }
void Vehicle::setVehicleType(const string& vType) { vehicleType = vType; }
void Vehicle::setEntryTime(time_t t) { entryTime = t; }
void Vehicle::setExitTime(time_t t) { exitTime = t; }

// ---- Getters ----
string Vehicle::getVehicleNumber() const { return vehicleNumber; }
string Vehicle::getVehicleType()   const { return vehicleType; }
time_t Vehicle::getEntryTime()     const { return entryTime; }
time_t Vehicle::getExitTime()      const { return exitTime; }

// ---- Utility ----
string Vehicle::getEntryTimeStr() const {
    if (entryTime == 0) return "N/A";
    char buf[64];
    struct tm* tm_info = localtime(&entryTime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    return string(buf);
}

string Vehicle::getExitTimeStr() const {
    if (exitTime == 0) return "Still Parked";
    char buf[64];
    struct tm* tm_info = localtime(&exitTime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    return string(buf);
}

double Vehicle::getParkingDurationHours() const {
    if (entryTime == 0 || exitTime == 0) return 0.0;
    double diff = difftime(exitTime, entryTime);
    return diff / 3600.0;
}

void Vehicle::displayVehicleInfo() const {
    cout << "  Vehicle No   : " << vehicleNumber << "\n";
    cout << "  Vehicle Type : " << vehicleType << "\n";
    cout << "  Entry Time   : " << getEntryTimeStr() << "\n";
    cout << "  Exit Time    : " << getExitTimeStr() << "\n";
}
