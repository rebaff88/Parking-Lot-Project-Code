// ============================================================
//  Vehicle.cpp
//  DEVELOPED BY: Reba Fatima Fawad (25L-2016) - Team Lead
// ============================================================
#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

using namespace std;

Vehicle::Vehicle() : entryTimestamp(0), exitTimestamp(0) {}

Vehicle::Vehicle(const string& vNum, const string& vType)
    : vehicleNumber(vNum), vehicleType(vType),
    entryTimestamp(0), exitTimestamp(0) {
}

void Vehicle::setVehicleNumber(const string& vNum) { vehicleNumber = vNum; }
void Vehicle::setVehicleType(const string& vType) { vehicleType = vType; }
void Vehicle::setEntryTime(time_t t) { entryTimestamp = t; }
void Vehicle::setExitTime(time_t t) { exitTimestamp = t; }

string Vehicle::getVehicleNumber() const { return vehicleNumber; }
string Vehicle::getVehicleType()   const { return vehicleType; }
time_t Vehicle::getEntryTimestamp()const { return entryTimestamp; }
time_t Vehicle::getExitTime()      const { return exitTimestamp; }

/*static*/ string Vehicle::timeToStr(time_t t) {
    if (t == 0) return "N/A";
    char buf[64];
    struct tm* tm_info = localtime(&t);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    return string(buf);
}

string Vehicle::getEntryTimeStr() const { return timeToStr(entryTimestamp); }
string Vehicle::getExitTimeStr()  const {
    if (exitTimestamp == 0) return "Still Parked";
    return timeToStr(exitTimestamp);
}

double Vehicle::getParkingDurationHours() const {
    if (entryTimestamp == 0 || exitTimestamp == 0) return 0.0;
    double diff = difftime(exitTimestamp, entryTimestamp);
    return diff / 3600.0;
}

void Vehicle::displayVehicleInfo() const {
    cout << "  Vehicle No   : " << vehicleNumber << "\n";
    cout << "  Vehicle Type : " << vehicleType << "\n";
    cout << "  Entry Time   : " << getEntryTimeStr() << "\n";
    cout << "  Exit Time    : " << getExitTimeStr() << "\n";
}