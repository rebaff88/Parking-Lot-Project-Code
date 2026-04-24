#include<iostream>
#include<fstream>//this library will handle file handling
#include<string>//library for string which will help to 
//access functions of strings 
using namespace std;
//creating classes:
// //now i am going to create a class of parking lots:
class ParkingLot {
	//also this class will be public
	//making data members and the functions public,
	//as they are going to get used in the main function:
public:
	int TotalParkingLots;
	int PricePerHour;
	int RevenueGenerated;
	//constructor; default
	ParkingLot() {
		TotalParkingLots = 0;
		PricePerHour = 0;
		RevenueGenerated = 0;
	}
};
// starting with the user class:
class User {
	//data members will be protected:
protected:
	//this is going to have two data members:
	string NameOfUser;
	string PasswordOfUser;//i have used string so that; the user
	//can eneter both letters and numbers.
public:
	//now i am going to create the functions, constructers:
	User() {
		NameOfUser = "No Name";
		PasswordOfUser = "No Password";
	}
	//creating a setter function
	void SetData(string u, string p) {
		NameOfUser = u;//setting the values of the data members 
		PasswordOfUser = p;
	}
	string GetNameOfUser() {
		//creating agetter function so that the desired value
		//will get returned:
		return NameOfUser;
	}
	string GetPasswordOfUser() {
		//now creating a getter function for the password of the user:
		return PasswordOfUser;
	}
};
//now here, the parent class is the user, below are some of 
//the child classes of it;
class Admin : public User {
	//this class is parent, 
public:
	Admin() {
		//default Constructor
	}
	//creating a  function to print the menu:
	void PrintTheAdminMenu() {
		cout << endl;
		for (int i = 0; i < 80; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "Admin Menu" << endl;
		string Menu[4][1] = {
			{"View Parking Slots"},
			{"View Revenue"},
			{"Change Rate"},
			{"Logout"}
		};
		//now strong this data in a dynamic array:
		string** DynamicMenu = new string * [4];
		for (int i = 0; i < 4; i++) {
			DynamicMenu[i] = new string[1];
			for (int j = 0; j < 1; j++) {
				DynamicMenu[i][j] = Menu[i][j];
				cout << i + 1 << " . " << DynamicMenu[i][j] << endl;
			}
		}//here the dynamic array will get printed and values will
		//get assigned to it
	}
};
class Customer : public User {
	//this class is parent, 
public:
	Customer() {
		//default Constructor
	}
	//creating a  function to print the menu:
	void PrintTheCustomerMenu() {
		cout << endl;
		for (int i = 0; i < 80; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "Customer Menu" << endl;
		string Menu[4][1] = {
			{"Park Vehicle"},
			{"Exit Vehicle"},
			{"View Slots"},
			{"Logout"}
		};
		cout << endl;
		//now strong this data in a dynamic array:
		string** DynamicMenu = new string * [4];
		for (int i = 0; i < 4; i++) {
			DynamicMenu[i] = new string[1];
			for (int j = 0; j < 1; j++) {
				DynamicMenu[i][j] = Menu[i][j];
				cout << i + 1 << " . " << DynamicMenu[i][j] << endl;
			}
		}//here the dynamic array will get printed and values will
		//get assigned to it
		cout << endl;
	}
};
//now iam going to create a class of vehicles which are going as objects
//in the parking lot:
class Vehicle {
	//making the data members and functions public:
public:
	string NumberPlateOfVehicle;//as the number plates can
	//be comprised of numeric and alphabetic letters
	string TypeOfVehicle;//is it for example car or what
	int VehicleTimeOfEntry;
	int VehicleTimeOfExit;//time required
};
//now here i am going to create some of the functions regarding the 
//various functions related to the user interface :
void SignUpFunction() {
	//this function will work on the signup, done:
	string NameOfTheUser;
	string PasswordOfUser;
	string RoleOfTheUser;//whether he is a client or admin;
	cout << "Please Enter Your Name : " << endl;
	cin >> NameOfTheUser;//input taken
	cout << "Please Enter Your Password" << endl;
}
int main() {
	//creating a parkinglott object:
	ParkingLot p1;
	return 0;
}