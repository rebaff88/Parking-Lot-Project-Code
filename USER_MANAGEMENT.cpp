
# include <iostream>
# include <string>
# include <fstream>
# include <ctime>


using namespace std;

class User {
protected:

	string username;
	string password;
	string role;


public:

	// DEFAULT CONSTRUCTOR IS DELIBERATELY LEFT EMPTY
	User() {}
	// PARAMETRIZED CONSTRUCTOR
	User(string u, string p, string r) {
		username = u;
		password = p;
		role = r;

	}

	// GETTERS

	string getUsername() {
		return username;
	}

	string getRole() {
		return role;
	}

	void SaveToFile() {
		// Opening the file here(Remember to add users.txt)
		ofstream file("users.txt", ios::app);

		//Writing to the file here
		file << username << "," << password << "," << role << endl;

		file.close();


		cout << "Account Created" << endl;


	}
	// We are using static keyword here because 
	// sometimes object is not created and without 
	// the static keyword compiler might throw error so 
	// static is used to search the object(username in this case)
	// without throwing an error

	static bool usernameExists(string uname) {
		
		ifstream file("users.txt");

		string u, p, r;


		// getline(file,variable,'comma') is the format below

		while (getline(file, u, ',')) {

			getline(file, p, ',');
			getline(file, r);


			if (u == uname) {
				file.close();

				return true; //INDICATES THAT USERNAME IS FOUND
			}



		}


		file.close();  //INDICATES THAT USERNAME IS NOT FOUND
		return false;


	}


	static string loginUser(string uname, string pwd) {

		ifstream file("users.txt");


		string u, p, r;


		while (getline(file, u, ',')) {

			getline(file, p, ',');
			getline(file, r);


			if (u == uname &&  p == pwd) {

				file.close();

				return r;

			}

			

		}

		file.close();

		cout << "WRONG CREDENTIALS, ACCESS NOT GRANTED" << endl;
		return "";


	}

	static bool deleteUser(string uname, string pwd) {


		ifstream file("users.txt");
		ofstream temp("temp.txt");


		string u, p, r;

		bool found = false;

		while (getline(file, u, ',')) {
			getline(file, p, ',');
			getline(file, r);

			if (u == uname && p == pwd) {

				found = true;
			}

			else {

				temp << u << "," << p << "," << r << endl;
			}



		}

		file.close();
		temp.close();


		remove("users.txt");
		(void)rename("temp.txt", "users.txt");




		return found;

	}


};

// INHERITANCE IS HAPPENING HERE 
// BASE CLASS= USER
// DERIVED CLASS= ADMIN
class Admin : public User {
public:
	// DEFAULT CONSTRUCTOR
	Admin() {
		role = "admin";
	}

	//  PARAMETERIZED CONSTRUCTOR
	Admin(string u,string p): User(u,p,"admin"){}

	// WE SHOW MENU HERE TO THE ADMIN 


	void ShowMenu() {

		int choice;
		while (true) {
			cout << "\n=====ADMIN MENU=====" << endl;
			cout << "1. View Parking Slots" << endl;
			cout << "2. View Revenue" << endl;
			cout << "3. Logout" << endl;
			cout << "Enter choice: ";
			cin >> choice;

			if (choice == 1) {
				cout << "Viewing Parking Slots...\n"; // your logic later
			}
			else if (choice == 2) {
				cout << "Viewing Revenue...\n"; // your logic later
			}
			else if (choice == 3) {
				cout << "Logging out...\n";
				break; // exits admin menu, goes back to main menu
			}
			else {
				cout << "Invalid choice!\n";
			}
		}
	}

};
// INHERITANCE IS HAPPENING HERE 
// BASE CLASS= USER
// DERIVED CLASS= CUSTOMER
class Customer : public User {
public:
	
	// DEFAULT CONSTRUCTOR
	Customer(){}
	//  PARAMETERIZED CONSTRUCTOR
	Customer(string u, string p):User (u,p,"customer"){}
	// WE SHOW MENU HERE TO THE CUSTOMER
	void ShowMenu() {
		int choice;
		while (true) {
			cout << "\n=====CUSTOMER MENU=====" << endl;
			cout << "1. Park Vehicle" << endl;
			cout << "2. Exit Vehicle" << endl;
			cout << "3. View Slots" << endl;
			cout << "4. Logout" << endl;
			cout << "Enter choice: ";
			cin >> choice;

			if (choice == 1) {
				cout << "Parking Vehicle...\n"; // your logic later
			}
			else if (choice == 2) {
				cout << "Exiting Vehicle...\n"; // your logic later
			}
			else if (choice == 3) {
				cout << "Viewing Slots...\n"; // your logic later
			}
			else if (choice == 4) {
				cout << "Logging out...\n";
				break; // exits customer menu, goes back to main menu
			}
			else {
				cout << "Invalid choice!\n";
			}
		}
	}

};

class Vehicle {
private:
	string VehicleNumber;
	string VehicleType;
	string EntryTime;
public:
	Vehicle(){}

	Vehicle(string Vnum, string Vtype) {

		VehicleNumber = Vnum;
		VehicleType = Vtype;

		EntryTime = get_Time();


	}
	// Code block to get systems time
	string get_Time() {

		time_t now = time(0);  // gets current time

		string t = ctime(&now); // converts the time to readable format

		t.erase(t.find('\n')); // remove the characters at the end to make it readable

		return t;

	}


	string GetVehicleNumber() {
		return VehicleNumber;
	}


	string GetVehicleType() {
		return VehicleType;
	}


	string GetEntryTime () {
		return EntryTime;
	}


	void DisplayInfo() {

		cout << "Vehicle Number: " << VehicleNumber << endl;
		cout << "Vehicle Type:   " << VehicleType << endl;
		cout << "Entry Time:" << EntryTime << endl;


	}

};

class ParkingSlot {

private:

	int SlotNumber;
	bool isOccupied;
	Vehicle vehicle;

public:

	ParkingSlot() {

		SlotNumber = 0;
		isOccupied = false;

	}

	ParkingSlot(int number) {
		SlotNumber = number;

		isOccupied = false;

	}


	int GetSlotNumber(){


		return SlotNumber;

	}

	bool GetisOccupied() {
		return isOccupied;


	}

	Vehicle getVehicle() {
		return vehicle;
	}

	void parkVehicle(Vehicle v) {
		vehicle = v;
		isOccupied = true;
	}

	void freeSlot() {
		isOccupied = false;
	}


	void displayStatus() {
		if (isOccupied) {
			cout << "Slot" << SlotNumber << " :OCCUPIED";
			cout << "(" << vehicle.GetVehicleNumber() << ")" << endl;

		}

		else {

			cout << "Slot" << SlotNumber << " :AVAILABLE" << endl;
		}

	}

};

int main() {

}
