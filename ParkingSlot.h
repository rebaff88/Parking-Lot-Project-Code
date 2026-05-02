#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include "Vehicle.h"

class ParkingSlot {
public:
    ParkingSlot();
    ParkingSlot(int num);

    int getSlotNumber() const;
    bool getIsOccupied() const;
    double getLockedRate() const;

    Vehicle getParkedVehicle() const;

    void parkVehicle(const Vehicle& v, double rate);
    void removeVehicle();

private:
    int slotNumber;
    bool occupied;
    Vehicle parkedVehicle;
    double lockedRate;
};

#endif // PARKINGSLOT_H