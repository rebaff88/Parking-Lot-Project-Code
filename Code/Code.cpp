// ============================================================
//  Vehicle.cpp
//  DEVELOPED BY: Reba Fatima Fawad (25L-2016) - Team Lead
// ============================================================
#include "Vehicle.h"//here i have mentioned the header file of vehicle class
//now thye contents of the header files acn be accessd using this  
#include <iostream>//main library
#include <iomanip>//format output, sets field for the output required 
//iomap: formsting, may be used in future
#include <sstream>//string stream library for string manipulation
//string stream  manipulation is accesd using this library
#include <cstring>//allows many functions which ican use for string functions and manipulation 
using namespace std;
Vehicle::Vehicle() : entryTimestamp(0), exitTimestamp(0) {}//here i am going to create a default consyructor
//:: is the scope resolution operastoer, now this is used to tell
//that this content is the data  mamber of the class which here ids the vehicle class
//object created, from constructor is called
//initailizing the time from Zero, as before the object which is a vehicle
//thye initialk time nis setted as to be zero
//constructor body is left empty as all,m the functions, i have performed in the initialization of the constructor itslef
Vehicle::Vehicle(const string& vNum, const string& vType)//here i am going to create a parametrized constructor 
    : vehicleNumber(vNum), vehicleType(vType),
    entryTimestamp(0), exitTimestamp(0) {//values are initialized and assigned 
}//moreover the constructors are left empty as I only wanted to assign the possible scenarios 
//so that any type of objects can be handled 
//now agfain using the format passing and initializiung the dsata members 
void Vehicle::setVehicleNumber(const string& vNum) { vehicleNumber = vNum; }//notations used from the libraries 
void Vehicle::setVehicleType(const string& vType) { vehicleType = vType; }
void Vehicle::setEntryTime(time_t t) { entryTimestamp = t; }//setting the values 
void Vehicle::setExitTime(time_t t) { exitTimestamp = t; }//when the vehicle is going to exit
string Vehicle::getVehicleNumber() const { return vehicleNumber; }//all the values which are
//going to get returned after a user is going to check in
string Vehicle::getVehicleType()   const { return vehicleType; }
time_t Vehicle::getEntryTimestamp()const { return entryTimestamp; }
time_t Vehicle::getExitTime()      const { return exitTimestamp; }
//again with these gatter functions the data menmbers of the object are returned
//here I am going to create some static funtiond and operatioons 
string Vehicle::timeToStr(time_t t) {//again i  am gloling to create a functioin wherre the time 9in seconds is attained
    //is going toi get converted into string rather then the secobnds
    if (t == 0) return "N/A";//hence 0 seconds, not available
    char buf[64];//making a charcter array 
    //initialized with the value of the character array as 64 is trhe
    //character capacity of thye data type character itself
   //from 0-63
    struct tm* tm_info = localtime(&t);//using struct: to initialize multiple data content in one place
    //for example time is enholding the : days, montthZ and hourZ
    //tm is pointer , pointing to localtime(&t): which will convt the raw data in seconds to readsable data ie string
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);//final formating to days-months etc
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
    return diff / 3600.0;//1 hour comprise 60 mins which inholds 60 seconds
    //that is why 60 x 60 =b 3600 seconds per hour
}
//now the details of the vehicles:
void Vehicle::displayVehicleInfo() const {
    //the function from the header file which will demonxstratye trhe details comprising
    //of the data members of the vehicle objects 
    cout << "  Vehicle No   : " << vehicleNumber << "\n";
    cout << "  Vehicle Type : " << vehicleType << "\n";
    cout << "  Entry Time   : " << getEntryTimeStr() << "\n";
    cout << "  Exit Time    : " << getExitTimeStr() << "\n";
}