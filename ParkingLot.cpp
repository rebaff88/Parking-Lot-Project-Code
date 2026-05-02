#include "ParkingLot.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <iostream>
using namespace std;
ParkingLot::ParkingLot() : totalSlots(0), totalRevenue(0.0), historyCount(0), USERS_FILE("users.txt"), HISTORY_FILE("history.txt"), SETTINGS_FILE("settings.txt")
{
    //initialize rate table
    rateTypes[0] = "Car"; rateValues[0] = 50.0;
    rateTypes[1] = "Bike"; rateValues[1] = 30.0;
    rateTypes[2] = "Truck"; rateValues[2] = 80.0;
    loadSettings();   //overwrites defaults if file exists
    loadHistory();
}
//index helper to check rate of vehicle type
int ParkingLot::rateIndex(const string& type) const {
    for (int i = 0; i < 3; i++)
        if (rateTypes[i] == type) return i;
    return 0;  // default to car index
}
//initialize parking lot
void ParkingLot::initialize(int numSlots) {
    totalSlots = numSlots;
    for (int i = 0; i < totalSlots; i++)
        parkingSlots[i] = ParkingSlot(i + 1);
    saveSettings();
}
bool ParkingLot::isInitialized() const { 
    return totalSlots > 0;
}
//LOAD AND SAVE INFO IN HISTORY FILE
// Format: username,vehicleNum,vehicleType,entry,exit,duration,fee,slot,lockedRate
void ParkingLot::loadHistory() {
    historyCount = 0;
    ifstream fin(HISTORY_FILE.c_str());
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line) && historyCount < MAX_HISTORY) {
        if (line.empty()) continue;
        stringstream ss(line);
        ParkingRecord rec;
        string dur, fee, slot, lockedRate;
        getline(ss, rec.username, '|');
        getline(ss, rec.vehicleNumber, '|');
        getline(ss, rec.vehicleType, '|');
        getline(ss, rec.entryTime, '|');
        getline(ss, rec.exitTime, '|');
        getline(ss, dur, '|');
        getline(ss, fee, '|');
        getline(ss, slot, '|');
        getline(ss, lockedRate, '|');
        
        rec.duration = atof(dur.c_str());
        rec.fee = atof(fee.c_str());
        rec.slotNumber = atoi(slot.c_str());
        if (lockedRate.empty() || lockedRate == "0") {
            rec.lockedRate = (rec.duration > 0) ? (rec.fee / rec.duration) : rateValues[0];
        }
        else {
            rec.lockedRate = atof(lockedRate.c_str());
        }
        history[historyCount++] = rec;
    }
    fin.close();
}
void ParkingLot::saveHistory() {
    ofstream fout(HISTORY_FILE.c_str());
    for (int i = 0; i < historyCount; i++) {
        const ParkingRecord& rec = history[i];
        fout << rec.username << "|" << rec.vehicleNumber << "|" << rec.vehicleType << "|" << rec.entryTime << "|" << rec.exitTime << "|"
            << fixed << setprecision(2) << rec.duration << "|" << rec.fee << "|" << rec.slotNumber << "|"  << rec.lockedRate << endl;
    } out.close();
}
//USER HISTORY OF PARKING LOT
int ParkingLot::getUserHistory(const string& username, ParkingRecord outRecs[], int maxCount) const {
    int count = 0;
    for (int i = 0; i < historyCount && count < maxCount; i++)
        if (history[i].username == username)
            outRecs[count++] = history[i];
    return count;
}
//COMPLETE HISTORY OF PARKING LOT
int ParkingLot::getAllHistory(ParkingRecord outRecs[], int maxCount) const {
    int count = (historyCount < maxCount) ? historyCount : maxCount;
    for (int i = 0; i < count; i++)
        outRecs[i] = history[i];
    return count;
}
//search vehicle (admin function)
bool ParkingLot::searchVehicle(const string& vNum, SlotSnapshot& outFound, string* outMsg) const {
    for (int i = 0; i < totalSlots; i++) {
        if (parkingSlots[i].getIsOccupied() && parkingSlots[i].getParkedVehicle().getVehicleNumber() == vNum) {
            outFound.slotNumber = parkingSlots[i].getSlotNumber();
            outFound.occupied = true;
            outFound.vehicleNumber = parkingSlots[i].getParkedVehicle().getVehicleNumber();
            outFound.vehicleType = parkingSlots[i].getParkedVehicle().getVehicleType();
            outFound.entryTime = parkingSlots[i].getParkedVehicle().getEntryTimeStr();
            outFound.lockedRate = parkingSlots[i].getLockedRate();
            if (outMsg) *outMsg = "Vehicle found at Slot " + to_string(outFound.slotNumber);
            return true;
        }
    }
    if (outMsg) *outMsg = "Vehicle " + vNum  " not found in active slots.";
    return false;
}
//revenue management (admin function)
double ParkingLot::getRateForType(const string& type) const {
    for (int i = 0; i < 3; i++)
        if (rateTypes[i] == type) return rateValues[i];
    return 50.0;  // fallback
}
void ParkingLot::setRateForType(const string& type, double rate) {
    for (int i = 0; i < 3; i++) {
        if (rateTypes[i] == type) {
            rateValues[i] = rate;
            break;
        }
    }
    saveSettings();  //immediately persisted — survives restart
}
//getter and setter
double ParkingLot::getHourlyRate() const { 
    return getRateForType("Car");
}
void ParkingLot::setHourlyRate(double r) { 
    setRateForType("Car", r);
}
//total revenue (admin func)
double ParkingLot::getTotalRevenue() const { 
    return totalRevenue;
}
//calculate fee based on parking time consumed
double ParkingLot::calculateFee(double hours, double ratePerHour) const {
    //agar hours 0 se kam hain (jaise foran nikal li) to kam az kam 0 balance
    if (hours <= 0) return 0.0;
    //total fee = time * rate
    return hours * ratePerHour;
}

