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

void ParkingLot::loadSettings() {
    ifstream fin(SETTINGS_FILE.c_str());
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // slots
        if (line.substr(0, 6) == "slots=") {
            totalSlots = atoi(line.substr(6).c_str());
            // revenue
        else if (line.substr(0, 8) == "revenue=") {
            totalRevenue = atof(line.substr(8).c_str());
        }
        // per-type rates  — rate_Car=, rate_Bike=, rate_Truck=
        else if (line.substr(0, 9) == "rate_Car=") {
            rateValues[0] = atof(line.substr(9).c_str());
        }
        else if (line.substr(0, 10) == "rate_Bike=") {
            rateValues[1] = atof(line.substr(10).c_str());
        }
        else if (line.substr(0, 11) == "rate_Truck=") {
            rateValues[2] = atof(line.substr(11).c_str());
        }
        // backward compat: old single "rate=" key → apply to all types
        else if (line.substr(0, 5) == "rate=" &&
            line.substr(0, 6) != "rate_") {
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
// ─── User management ─────────────────────────────────────────

bool ParkingLot::userExists(const string& uname) const {
    ifstream fin(USERS_FILE);
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // CHANGED: Using '|' as separator
        if (line.substr(0, line.find('|')) == uname) return true;
    }
    return false;
}

bool ParkingLot::signupUser(const string& uname, const string& pwd,
    const string& role, string* outMsg) {

    // ─── VALIDATION CHECKS ───
    // 1. Username length
    if (uname.length() < 6 || uname.length() > 16) {
        if (outMsg) *outMsg = "Username must be between 6 and 16 characters!";
        return false;
    }
    // 2. Username illegal character
    if (uname.find('|') != string::npos) {
        if (outMsg) *outMsg = "Username cannot contain the '|' character!";
        return false;
    }
    // 3. Password length
    if (pwd.length() < 8 || pwd.length() > 16) {
        if (outMsg) *outMsg = "Password must be between 8 and 16 characters!";
        return false;
    }
    // 4. Password illegal character
    if (pwd.find('|') != string::npos) {
        if (outMsg) *outMsg = "Password cannot contain the '|' character!";
        return false;
    }

    if (userExists(uname)) {
        if (outMsg) *outMsg = "Username already exists!";
        return false;
    }

    ofstream fout(USERS_FILE, ios::app);
    // CHANGED: Saved using '|' separator
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
        // CHANGED: Read using '|' separator
        getline(ss, u, '|');
        getline(ss, p, '|');
        getline(ss, r, '|');
        if (u == uname && p == pwd) {
            if (r == "Admin") return new Admin(u, p);
            else              return new Customer(u, p);
        }
    }
    return nullptr;
}

bool ParkingLot::deleteUser(const string& unameDisplay, string* outMsg) {
    // UI se ab "username (Role)" aayega, isliye asal username nikalna zaroori hai:
    string actualUname = unameDisplay;
    size_t pos = actualUname.find(" (");
    if (pos != string::npos) {
        actualUname = actualUname.substr(0, pos); // Sirf naam wala hissa alag kar liya
    }

    ifstream fin(USERS_FILE);
    if (!fin.is_open()) { if (outMsg) *outMsg = "No users file."; return false; }

    const int MAX_U = 1000;
    string lines[MAX_U];
    int count = 0;
    string line;
    bool found = false;

    while (getline(fin, line) && count < MAX_U) {
        if (line.empty()) continue;

        // Asal username se match karna
        if (line.substr(0, line.find('|')) == actualUname) {
            found = true;
            continue; // Is line ko skip kar do (yani delete kar do)
        }
        lines[count++] = line;
    }
    fin.close();

    if (!found) { if (outMsg) *outMsg = "User not found."; return false; }

    ofstream fout(USERS_FILE);
    for (int i = 0; i < count; i++) fout << lines[i] << "\n";

    if (outMsg) *outMsg = "User '" + actualUname + "' deleted successfully.";
    return true;
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

// ─── Park vehicle ─────────────────────────────────────────────
bool ParkingLot::parkVehicle(const string& username,
    const string& vNum,
    const string& vType,
    int& assignedSlot,
    string* outMsg) {
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
    oss << "Vehicle parked at Slot " << assignedSlot
        << "  |  Rate locked: Rs. "
        << fixed << setprecision(2) << lockedRate << "/hr";
    if (outMsg) *outMsg = oss.str();
    return true;
}

// ─── Checkout vehicle ─────────────────────────────────────────
bool ParkingLot::checkoutVehicle(const string& username,
    int slotNum,
    ParkingRecord& outRecord,
    double& outFee,
    string* outMsg) {
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
int ParkingLot::getAllSlotsSnapshot(SlotSnapshot outSnaps[],
    int maxCount) const {
    int count = (totalSlots < maxCount) ? totalSlots : maxCount;
    for (int i = 0; i < count; i++) {
        SlotSnapshot ss;
        ss.slotNumber = parkingSlots[i].getSlotNumber();
        ss.occupied = parkingSlots[i].getIsOccupied();
        if (ss.occupied) {
            ss.vehicleNumber = parkingSlots[i].getParkedVehicle().getVehicleNumber();
            ss.vehicleType = parkingSlots[i].getParkedVehicle().getVehicleType();
            ss.entryTime = parkingSlots[i].getParkedVehicle().getEntryTimeStr();
            ss.lockedRate = parkingSlots[i].getLockedRate();
        }
        outSnaps[i] = ss;
    }
    return count;
} 
    int    ParkingLot::getTotalSlots()     const { return totalSlots; }
int    ParkingLot::getOccupiedSlots()  const {
    int c = 0;
    for (int i = 0; i < totalSlots; i++)
        if (parkingSlots[i].getIsOccupied()) c++;
    return c;
}
int    ParkingLot::getAvailableSlots() const {
    return totalSlots - getOccupiedSlots();
}
// ─── Helper Functions ──────────────────────────────────────────

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


































































}
