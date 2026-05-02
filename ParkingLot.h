#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <string>
#include <ctime>
#include "ParkingSlot.h"
#include "User.h"
using namespace std;
//maximum capacities
static const int MAX_SLOTS = 500;
static const int MAX_HISTORY = 5000;
static const int MAX_USERS = 500;
class ParkingRecord {
public:
    string username;
    string vehicleNumber;
    string vehicleType;
    string entryTime;
    string exitTime;
    double duration;
    double fee;
    double lockedRate;
    int slotNumber;
    ParkingRecord() : duration(0.0), fee(0.0), lockedRate(0.0), slotNumber(0) {
    }
};
class SlotSnapshot {
public:
    int slotNumber;
    bool occupied;
    string vehicleNumber;
    string vehicleType;
    string entryTime;
    double lockedRate;
    SlotSnapshot() : slotNumber(0), occupied(false), lockedRate(0.0) {
    }
};
class ParkingLot {
public:
    ParkingLot();
    void initialize(int numSlots);
    bool isInitialized() const;
    //search vehicle (admin func)
    bool searchVehicle(const string& vNum, SlotSnapshot& outFound, string* outMsg = nullptr) const;
    //history
    //returns count, fills outRecs[0..count-1]
    int  getUserHistory(const string& username, ParkingRecord outRecs[], int maxCount) const;
    int  getAllHistory(ParkingRecord outRecs[], int maxCount) const;
    //revenue management (admin func)
    double getTotalRevenue()   const;
    double getRateForType(const string& type) const;
    void setRateForType(const string& type, double rate);
    double getHourlyRate() const;
    void   setHourlyRate(double r);
private:
    int totalSlots;
    double totalRevenue;
    //type rates stored as parallel arrays (Car/Bike/Truck)
    string rateTypes[3];
    double rateValues[3];
    ParkingSlot parkingSlots[MAX_SLOTS];
    ParkingRecord history[MAX_HISTORY];
    int historyCount;
    const string USERS_FILE;
    const string HISTORY_FILE;
    const string SETTINGS_FILE;
    double calculateFee(double hours, double rate) const;
    void loadSettings();
    void saveSettings();
    void loadHistory();
    void saveHistory();
    //helper to get rate array index for a type
    int  rateIndex(const string& type) const;
};
#endif // PARKINGLOT_H

