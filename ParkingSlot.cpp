#include "ParkingSlot.h"
ParkingSlot::ParkingSlot() : slotNumber(0), occupied(false), lockedRate(0.0) {
}
ParkingSlot::ParkingSlot(int num)
    : slotNumber(num), occupied(false), lockedRate(0.0) {
}
int    ParkingSlot::getSlotNumber()   const { return slotNumber; }
bool   ParkingSlot::getIsOccupied()   const { return occupied; }
double ParkingSlot::getLockedRate()   const { return lockedRate; }
Vehicle ParkingSlot::getParkedVehicle() const { return parkedVehicle; }
void ParkingSlot::parkVehicle(const Vehicle& v, double rate) {
    parkedVehicle = v;
    occupied = true;
    lockedRate = rate;
}
void ParkingSlot::removeVehicle() {
    parkedVehicle = Vehicle();
    occupied = false;
    lockedRate = 0.0;
}