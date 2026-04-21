#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// ================= USER CLASS =================
class User {
protected:
    string username, password;

public:
    void setData(string u, string p) {
        username = u;
        password = p;
    }

    string getUsername() { return username; }
    string getPassword() { return password; }
};

// ================= ADMIN =================
class Admin : public User {
public:
    void menu() {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. View Parking Slots\n";
        cout << "2. View Revenue\n";
        cout << "3. Change Rate\n";
        cout << "4. Logout\n";
    }
};

// ================= CUSTOMER =================
class Customer : public User {
public:
    void menu() {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Exit Vehicle\n";
        cout << "3. View Slots\n";
        cout << "4. Logout\n";
    }
};

// ================= VEHICLE =================
class Vehicle {
public:
    string number, type;
    int entryTime, exitTime;
};

// ================= SLOT =================
class ParkingSlot {
public:
    int slotNo;
    bool occupied;
    Vehicle v;
};

// ================= PARKING LOT =================
class ParkingLot {
public:
    ParkingSlot slots[50];
    int totalSlots;
    int rate = 10; // per hour
    int revenue = 0;

    void initialize(int n) {
        totalSlots = n;
        for (int i = 0; i < n; i++) {
            slots[i].slotNo = i + 1;
            slots[i].occupied = false;
        }
    }

    void displaySlots() {
        cout << "\n--- Parking Slots ---\n";
        for (int i = 0; i < totalSlots; i++) {
            cout << "Slot " << slots[i].slotNo << " : ";
            if (slots[i].occupied) cout << "Occupied\n";
            else cout << "Available\n";
        }
    }

    void parkVehicle() {
        string num, type;
        int time;

        cout << "Enter Vehicle Number: ";
        cin >> num;
        cout << "Enter Vehicle Type: ";
        cin >> type;
        cout << "Enter Entry Time (hour): ";
        cin >> time;

        for (int i = 0; i < totalSlots; i++) {
            if (!slots[i].occupied) {
                slots[i].occupied = true;
                slots[i].v.number = num;
                slots[i].v.type = type;
                slots[i].v.entryTime = time;

                cout << "Vehicle parked at slot " << slots[i].slotNo << endl;
                return;
            }
        }

        cout << "Parking Full!\n";
    }

    void exitVehicle() {
        string num;
        int exitTime;

        cout << "Enter Vehicle Number: ";
        cin >> num;

        for (int i = 0; i < totalSlots; i++) {
            if (slots[i].occupied && slots[i].v.number == num) {

                cout << "Enter Exit Time (hour): ";
                cin >> exitTime;

                int duration = exitTime - slots[i].v.entryTime;
                int fee = duration * rate;
                revenue += fee;

                // Save to file (HISTORY)
                ofstream file("history.txt", ios::app);
                file << num << " "
                    << slots[i].v.type << " "
                    << duration << " "
                    << fee << endl;
                file.close();

                slots[i].occupied = false;

                cout << "Fee: " << fee << endl;
                return;
            }
        }

        cout << "Vehicle not found!\n";
    }
};

// ================= USER MANAGEMENT (YOUR PART) =================

// SIGNUP
void signup() {
    string username, password, role;

    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Role (Admin/Customer): ";
    cin >> role;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << " " << role << endl;
    file.close();

    cout << "Signup Successful!\n";
}

// LOGIN
bool login(string& role, string& username) {
    string u, p, r;
    string inputUser, inputPass;

    cout << "Enter Username: ";
    cin >> inputUser;
    cout << "Enter Password: ";
    cin >> inputPass;

    ifstream file("users.txt");

    while (file >> u >> p >> r) {
        if (u == inputUser && p == inputPass) {
            role = r;
            username = u;
            return true;
        }
    }

    return false;
}

// DELETE ACCOUNT
void deleteAccount(string currentUser) {
    ifstream file("users.txt");
    ofstream temp("temp.txt");

    string u, p, r;

    while (file >> u >> p >> r) {
        if (u != currentUser) {
            temp << u << " " << p << " " << r << endl;
        }
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    cout << "Account Deleted!\n";
}

// ================= MAIN =================
int main() {

    ParkingLot p;
    p.initialize(5);

    int choice;

    while (true) {
        cout << "\n1. Signup\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            signup();
        }

        else if (choice == 2) {
            string role, username;

            if (login(role, username)) {

                if (role == "Admin") {
                    Admin a;
                    int ch;

                    while (true) {
                        a.menu();
                        cin >> ch;

                        if (ch == 1) p.displaySlots();
                        else if (ch == 2) cout << "Revenue: " << p.revenue << endl;
                        else if (ch == 3) {
                            cout << "Enter new rate: ";
                            cin >> p.rate;
                        }
                        else if (ch == 4) break;
                    }
                }

                else {
                    Customer c;
                    int ch;

                    while (true) {
                        c.menu();
                        cin >> ch;

                        if (ch == 1) p.parkVehicle();
                        else if (ch == 2) p.exitVehicle();
                        else if (ch == 3) p.displaySlots();
                        else if (ch == 4) {
                            deleteAccount(username);
                            break;
                        }
                    }
                }

            }
            else {
                cout << "Invalid Login!\n";
            }
        }

        else {
            break;
        }
    }

    return 0;
}