Parking Operations Module
Overview

This branch implements the core parking operations logic of the Parking Management System. It focuses on managing vehicle entry, exit, slot allocation, fee calculation, and parking history. The module is designed to handle parking activities efficiently while keeping the logic simple and easy to understand.

Functionality

The system allows a vehicle to enter by providing its number and type, after which the first available parking slot is automatically assigned and the entry time is recorded. When a vehicle exits, the user can provide either the vehicle number or slot number. The system then records the exit time, calculates the total parking duration, and generates the parking fee based on a fixed hourly rate.

It also maintains a parking history by storing details such as vehicle number, slot number, duration, and fee paid using file handling. In addition, the system provides a real-time view of parking slots, indicating which slots are occupied or available. A search feature is included to locate a parked vehicle using its number and retrieve its current status.

Implementation Details

The module is implemented using arrays for slot management and dynamic memory allocation to support flexible parking capacity. Functions are used to separate different operations such as entry, exit, search, and billing, ensuring modular and organized code. File handling is used to store parking history for future reference.

Notes

This branch is limited to parking operations only and does not include user management or administrative features. It is implemented using basic C++ concepts with simple logic and standard programming structures.

Contributor

Abdullah Yasar
25L-2056
