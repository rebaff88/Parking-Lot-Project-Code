//DEVELOPED BY: Abdullah Saleem (25L-5683)
//Responsibility: Base User class + Admin & Customer (Inheritance)
#include "User.h"
#include <iostream>
using namespace std;
//base user
User::User() : role("Customer") {}
User::User(const string& uname, const string& pwd, const string& r) : username(uname), password(pwd), role(r) {}
//getters and setters
string User::getUsername() const { 
    return username;
}
string User::getPassword() const {
    return password;
}
string User::getRole() const {
    return role; 
}
void User::setUsername(const string& u) { 
    username = u;
}
void User::setPassword(const string& p) {
    password = p; 
}

string User::serialize() const {
    return username + "," + password + "," + role;
}
//validate
bool User::matchCredentials(const string& uname, const string& pwd) const {
    return (username == uname && password == pwd);
}
//admin
Admin::Admin() {
    role = "Admin";
}
Admin::Admin(const string& uname, const string& pwd) : User(uname, pwd, "Admin") {}
//display menu
void Admin::showMenu() {
    cout << "\n==============================" << endl;
    cout << "   ADMIN PANEL | " << username << endl;
    cout << "==============================" << endl;
    cout << " [1] View Parking Slot Status" << endl;
    cout << " [2] View All Parking History" << endl;
    cout << " [3] View Total Revenue" << endl;
    cout << " [4] Update Hourly Rate" << endl;
    cout << " [5] Search Vehicle" << endl;
    cout << " [6] Delete User Account" << endl;
    cout << " [0] Logout" << endl;
    cout << "------------------------------" << endl;
    cout << " Enter Your Choice: ";
}
//customer/user
Customer::Customer() { role = "Customer"; }
Customer::Customer(const string& uname, const string& pwd) : User(uname, pwd, "Customer") {}

void Customer::showMenu() {
    cout << "\n==============================" << endl;
    cout << "  CUSTOMER PANEL | " << username << endl;
    cout << "==============================" << endl;
    cout << " [1] View Available Slots" << endl;
    cout << " [2] Park My Vehicle" << endl;
    cout << " [3] Exit Parking (Checkout)" << endl;
    cout << " [4] View My Parking History" << endl;
    cout << " [0] Logout" << endl;
    cout << "------------------------------" << endl;
    cout << "Enter Your Choice: ";
}
