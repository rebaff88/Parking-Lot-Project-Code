#include "ParkingLot.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <iostream>
using namespace std;
//25L-5683
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
//25L-2056
//setting & file format, slots=20, revenue=1500.00, rate_Car=50.00, rate_Bike=30.00, rate_Truck=80.00
void ParkingLot::loadSettings() {
    ifstream fin(SETTINGS_FILE.c_str());
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // slots
        if (line.substr(0, 6) == "Slots = ") {
            totalSlots = atoi(line.substr(6).c_str());
            // revenue
        else if (line.substr(0, 8) == "Revenue = ") {
            totalRevenue = atof(line.substr(8).c_str());
        }
        // per-type rates  — rate_Car=, rate_Bike=, rate_Truck=
        else if (line.substr(0, 9) == "rate_Car = ") {
            rateValues[0] = atof(line.substr(9).c_str());
        }
        else if (line.substr(0, 10) == "rate_Bike = ") {
            rateValues[1] = atof(line.substr(10).c_str());
        }
        else if (line.substr(0, 11) == "rate_Truck=") {
            rateValues[2] = atof(line.substr(11).c_str());
        }
        // backward compat: old single "rate=" key → apply to all types
        else if (line.substr(0, 5) == "rate=" && line.substr(0, 6) != "rate_") {
            double r = atof(line.substr(5).c_str());
            rateValues[0] = r;
            rateValues[1] = r;
            rateValues[2] = r;
        }
        }
        fin.close();
        // Rebuild slots array from loaded totalSlots
        if (totalSlots > 0) {
            for (int i = 0; i < totalSlots; i++)
                parkingSlots[i] = ParkingSlot(i + 1);
        }
    }
void ParkingLot::saveSettings() {
    ofstream fout(SETTINGS_FILE.c_str());
    fout << "Slots = " << totalSlots << endl << "Revenue = " << fixed << setprecision(2) << totalRevenue << endl << "rate_Car = " << rateValues[0] << endl << "rate_Bike = " << rateValues[1] << endl
     << "rate_Truck = " << rateValues[2] << endl;
    fout.close();
}
//user manangement
bool ParkingLot::userExists(const string& uname) const {
    ifstream fin(USERS_FILE);
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        //Using '|' as separator
        if (line.substr(0, line.find('|')) == uname) return true;
    }
    return false;
}
bool ParkingLot::signupUser(const string& uname, const string& pwd,
    const string& role, string* outMsg) {
//VALIDATION CHECKS
    //username length
    if (uname.length() < 6 || uname.length() > 16) {
        if (outMsg) *outMsg = "Username must be between 6 and 16 characters!";
        return false;
    }
    //illegal character
    if (uname.find('|') != string::npos) {
        if (outMsg) *outMsg = "Username cannot contain the '|' character!";
        return false;
    }
    //password length
    if (pwd.length() < 8 || pwd.length() > 16) {
        if (outMsg) *outMsg = "Password must be between 8 and 16 characters!";
        return false;
    }
    //password illegal character
    if (pwd.find('|') != string::npos) {
        if (outMsg) *outMsg = "Password cannot contain the '|' character!";
        return false;
    }
    if (userExists(uname)) {
        if (outMsg) *outMsg = "Username already exists!";
        return false;
    }
    ofstream fout(USERS_FILE, ios::app);
    //saved using '|' separator
    fout << uname << "|" << pwd << "|" << role << "\n";
    if (outMsg) *outMsg = "Account created for: " + uname + " [" + role + "]";
    return true;
}
User* ParkingLot::loginUser(const string& uname, const string& pwd) {
    ifstream fin(USERS_FILE);
    if (!fin.is_open()) return nullptr;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string u, p, r;
        //read using '|' separator
        getline(ss, u, '|');
        getline(ss, p, '|');
        getline(ss, r, '|');
        if (u == uname && p == pwd) {
            if (r == "Admin") return new Admin(u, p);
            else return new Customer(u, p);
        }
    }
    return nullptr;
}

int ParkingLot::getAllUsernames(string outUsers[], int maxLen) const {
    ifstream fin(USERS_FILE);
    int count = 0;
    if (!fin.is_open()) return 0;
    string line;
    while (getline(fin, line) && count < maxLen) {
        if (line.empty()) continue;
        stringstream ss(line);
        string u, p, r;
        // Pipe '|' se alag alag values read karna
        getline(ss, u, '|');
        getline(ss, p, '|');
        getline(ss, r, '|');
        // Yahan hum Username aur Role ko aapas mein jor kar bhej rahe hain
        outUsers[count++] = u + " (" + r + ")";
    }
    return count;
}
//parking operations logic
//park vehicle
bool ParkingLot::parkVehicle(const string& username, const string& vNum, const string& vType, int& assignedSlot, string* outMsg) {
    (void)username;
    if (totalSlots == 0) {
        if (outMsg) *outMsg = "Parking lot not initialized!";
        return false;
    }
    if (findSlotByVehicle(vNum) != -1) {
        if (outMsg) *outMsg = "Vehicle " + vNum + " is already parked!";
        return false;
    }
    int idx = findFirstAvailableSlot();
    if (idx == -1) {
        if (outMsg) *outMsg = "No available slots!";
        return false;
    }
    Vehicle v(vNum, vType);
    v.setEntryTime(time(nullptr));
    double lockedRate = getRateForType(vType);
    parkingSlots[idx].parkVehicle(v, lockedRate);
    assignedSlot = parkingSlots[idx].getSlotNumber();
    ostringstream oss;
    oss << "Vehicle parked at Slot " << assignedSlot << "  |  Rate locked: Rs. " << fixed << setprecision(2) << lockedRate << "/hr";
    if (outMsg) *outMsg = oss.str();
    return true;
}
//checkout vehicle
bool ParkingLot::checkoutVehicle(const string& username, int slotNum, ParkingRecord& outRecord, double& outFee, string* outMsg) {
    int idx = slotNum - 1;
    if (idx < 0 || idx >= totalSlots || !parkingSlots[idx].getIsOccupied()) {
        if (outMsg) *outMsg = "Invalid or empty slot number: " + to_string(slotNum);
        return false;
    }
    Vehicle v = parkingSlots[idx].getParkedVehicle();
    double  lockedRate = parkingSlots[idx].getLockedRate();   
    v.setExitTime(time(nullptr));
    double hours = v.getParkingDurationHours();
    double fee = calculateFee(hours, lockedRate);
    totalRevenue += fee;
    saveSettings();
    outRecord.username = username;
    outRecord.vehicleNumber = v.getVehicleNumber();
    outRecord.vehicleType = v.getVehicleType();
    outRecord.entryTime = v.getEntryTimeStr();
    outRecord.exitTime = v.getExitTimeStr();
    outRecord.duration = hours;
    outRecord.fee = fee;
    outRecord.lockedRate = lockedRate;
    outRecord.slotNumber = slotNum;
    outFee = fee;
    if (historyCount < MAX_HISTORY)
        history[historyCount++] = outRecord;
    saveHistory();
    parkingSlots[idx].removeVehicle();
    if (outMsg) *outMsg = "Checkout successful.";
    return true;
}
//get stas
int ParkingLot::getTotalSlots() const { return totalSlots; }
int ParkingLot::getOccupiedSlots()  const {
    int c = 0;
    for (int i = 0; i < totalSlots; i++)
        if (parkingSlots[i].getIsOccupied()) c++;
    return c;
}
int ParkingLot::getAvailableSlots() const {
    return totalSlots - getOccupiedSlots();
}
//helpers functions
int ParkingLot::findSlotByVehicle(const string& vNum) const {
    for (int i = 0; i < totalSlots; i++) {
        // Check if slot is occupied and vehicle number matches
        if (parkingSlots[i].getIsOccupied()) {
            if (parkingSlots[i].getParkedVehicle().getVehicleNumber() == vNum) {
                return i; // Slot index mil gaya
            }
        }
    }
    return -1; // Gaari nahi mili
}
int ParkingLot::findFirstAvailableSlot() const {
    for (int i = 0; i < totalSlots; i++) {
        // Agar slot khali hai to uska index return kar do
        if (!parkingSlots[i].getIsOccupied()) {
            return i;
        }
    }
    return -1; // Parking full hai
}



