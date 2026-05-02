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
