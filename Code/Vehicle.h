#ifndef VEHICLE_H//to include file if previouzsly it was not definhed
#define VEHICLE_H//format of the header file:
//header file 
// as another file(.cpp)can also access the header file to
// //invlove the contents of the file
// /so for the compiler to avoiod errors we arew adding the to[p labels
// ============================================================
//  Vehicle.h
//  DEVELOPED BY: Reba Fatima Fawad (25L-2016) - Team Lead
//  Responsibility: Vehicle entity + encapsulated data; which are the parts of content covered in OOP this semester
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
    //time_t is accesedd from the library of ctime 
    //time_t itsekf is a data member whioch stores ther data in itself in the form of seconds
    // //entry and exit will get stored in the form oif seconds
public:
    //for direct accessing the functions and the constructors of the object of trhe class
    Vehicle();//defult constructor has been cereeated here for the objects which does not enhoolds any value
    //or is not parametrized
    Vehicle(const string& vNum, const string& vType);//parametrized constructors
    //for the parametrized constructors we are passing the  now this will work for theb  paasing of the 
    //vehiclew number and the type of thje vehicle 
    void setVehicleNumber(const string& vNum);//functions for different actions regarding the class respectively
    //the above function is the setter function of the object
    void setVehicleType(const string& vType);
    void setEntryTime(time_t t);
    void setExitTime(time_t t);
    //till here i ahve made the setters for the objects contenty
    //here i am going to create the getter fuctions of the cointent
    string getVehicleNumber() const;//using const not to modify the objecvt oitsle just peerfornming the function on the data memebers of the object
    string getVehicleType()   const;
    time_t getEntryTimestamp() const;//getting the data in a readable form
    time_t getExitTime()       const;
    string getEntryTimeStr()  const;
    string getExitTimeStr()   const;
    double getParkingDurationHours() const;//double for attaing the time for example 2.5 instread of 2 hours and 30 mins 
    void displayVehicleInfo() const;//this function will display trhe contents(genefral)
private:
    static string timeToStr(time_t t);//this data member is static because the function timeToStr itself is as mere utility function
    //this allows thye converstion of the time we have attained to string
};
//here is the end of the header file and i have created the class of the vehicle with all the data members and functions which are required for the operations of the parking management system
#endif // VEHICLE_H