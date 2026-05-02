#ifndef VEHICLE_H
#define VEHICLE_H//format of the header file:
//header file 
// ============================================================
//  Vehicle.h
//  DEVELOPED BY: Reba Fatima Fawad (25L-2016) - Team Lead
//  Responsibility: Vehicle entity + encapsulated data
// ============================================================
#include <string>//library foir string 
#include <ctime> //libraries used for tinme manipulation and for string handling 
using namespace std;
class Vehicle {//here in am going to cretae the class of the vehicle 
private://creating the data members as private 
    string vehicleNumber;//the number; other essentials are:
    string vehicleType;//what type of the vehicle 
    time_t entryTimestamp;//entry time of the vehicle 
    time_t exitTimestamp;//exit time of the vehicle 
public:
    Vehicle();//defult constructor 
    Vehicle(const string& vNum, const string& vType);//parametrized constructors
    void setVehicleNumber(const string& vNum);//functions for different actions regarding the class respectively
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
//here is the end of the header file and i have created the class of the vehicle with all the data members and functions which are required for the operations of the parking management system
#endif // VEHICLE_H