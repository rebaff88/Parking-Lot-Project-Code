#ifndef VEHICLE_H
#define VEHICLE_H

// ============================================================
//  Vehicle.h
//  DEVELOPED BY: Reba Fatima Fawad (25L-2016) - Team Lead
//  Responsibility: Vehicle entity + encapsulated data
// ============================================================

#include <string>
#include <ctime> 

using namespace std;

class Vehicle {
private:
    string vehicleNumber;
    string vehicleType;     // Car, Bike, Truck
    time_t entryTimestamp;
    time_t exitTimestamp;

public:
    Vehicle();
    Vehicle(const string& vNum, const string& vType);

    void setVehicleNumber(const string& vNum);
    void setVehicleType(const string& vType);
    void setEntryTime(time_t t);
    void setExitTime(time_t t);

    string getVehicleNumber() const;
    string getVehicleType()   const;
    time_t getEntryTimestamp() const;
    time_t getExitTime()       const;

    string getEntryTimeStr()  const;
    string getExitTimeStr()   const;
    double getParkingDurationHours() const;

    void displayVehicleInfo() const;

private:
    static string timeToStr(time_t t);
};

#endif // VEHICLE_H