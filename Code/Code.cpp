// ============================================================
//  Vehicle.cpp
//  DEVELOPED BY: Reba Fatima Fawad (25L-2016) - Team Lead
// ============================================================
#include "Vehicle.h"//here i have mentioned the header file of vehicle class
#include <iostream>//main library
#include <iomanip>//format output, sets field for the output required 
#include <sstream>//string stream library for string manipulation
#include <cstring>//allows many functions which ican use for string functions and manipulation 
using namespace std;
Vehicle::Vehicle() : entryTimestamp(0), exitTimestamp(0) {}//here i am going to create a default consyructor
Vehicle::Vehicle(const string& vNum, const string& vType)//here i am going to create a parametrized constructor 
    : vehicleNumber(vNum), vehicleType(vType),
    entryTimestamp(0), exitTimestamp(0) {//values are initialized and assigned 
}//moreover the constructors are left empty as I only wanted to assign the possible scenarios 
//so that any type of objects can be handled 
void Vehicle::setVehicleNumber(const string& vNum) { vehicleNumber = vNum; }//notations used from the libraries 
void Vehicle::setVehicleType(const string& vType) { vehicleType = vType; }
void Vehicle::setEntryTime(time_t t) { entryTimestamp = t; }//setting the values 
void Vehicle::setExitTime(time_t t) { exitTimestamp = t; }//when the vehicle is going to exit
string Vehicle::getVehicleNumber() const { return vehicleNumber; }//all the values which are
//going to get returned after a user is going to check in
string Vehicle::getVehicleType()   const { return vehicleType; }
time_t Vehicle::getEntryTimestamp()const { return entryTimestamp; }
time_t Vehicle::getExitTime()      const { return exitTimestamp; }
//here I am going to create some static funtiond and operatioons 
string Vehicle::timeToStr(time_t t) {
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
//now the details of the vehicles:
void Vehicle::displayVehicleInfo() const {
    cout << "  Vehicle No   : " << vehicleNumber << "\n";
    cout << "  Vehicle Type : " << vehicleType << "\n";
    cout << "  Entry Time   : " << getEntryTimeStr() << "\n";
    cout << "  Exit Time    : " << getExitTimeStr() << "\n";
}