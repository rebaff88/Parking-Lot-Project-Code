#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <string>
#include <ctime>
#include "ParkingSlot.h"
#include "User.h"
using namespace std;

static const int MAX_SLOTS = 500;
static const int MAX_HISTORY = 5000;
static const int MAX_USERS = 500;

class SlotSnapshot {
public:
    int    slotNumber;
    bool   occupied;
    string vehicleNumber;
    string vehicleType;
    string entryTime;
    double lockedRate;

    SlotSnapshot()
        : slotNumber(0), occupied(false), lockedRate(0.0) {
    }
};

  // User management
    bool signupUser(const string& uname, const string& pwd,
        const string& role, string* outMsg = nullptr);
    User* loginUser(const string& uname, const string& pwd);
    bool  deleteUser(const string& uname, string* outMsg = nullptr);
    // Returns count; fills outNames[0..count-1]
    int   getAllUsernames(string outNames[], int maxCount) const;
    // Parking operations
    bool parkVehicle(const string& username, const string& vNum,
        const string& vType, int& assignedSlot,
        string* outMsg = nullptr);
    bool checkoutVehicle(const string& username, int slotNum,
        ParkingRecord& outRecord, double& outFee,
        string* outMsg = nullptr);

 int  getAllSlotsSnapshot(SlotSnapshot outSnaps[], int maxCount) const;

 int    getTotalSlots()     const;
    int    getOccupiedSlots()  const;
    int    getAvailableSlots() const;

  bool   userExists(const string& uname) const;
    int    findFirstAvailableSlot() const;
    int    findSlotByVehicle(const string& vNum) const;

};

#endif
