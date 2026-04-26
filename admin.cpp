#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
using namespace std;
class parkingSlot {
private:
	int slotNum;
	int entryTime; //stored as HH:MM  e.g. 14:30 = 2:30 PM
	int exitTime;
	string vehicleNum;
	string vehicleType;
	bool isOccupied;
public:
	parkingSlot() { //default constructor
		slotNum = 0;
		entryTime = 0;
		exitTime = 0;
		vehicleNum = "";
		vehicleType = "";
		isOccupied = false;
	}
	//setters and getters
	void setSlot(int n) { slotNum = n; }
	void setStatus(bool occ) { isOccupied = occ; }
	void setVehicleNum(string vn) { vehicleNum = vn; }
	void setVehicleType(string vt) { vehicleType = vt; }
	void setEntryTime(int ent) { entryTime = ent; }
	void setExitTime(int ext) { exitTime = ext; }
	int getSlotNum() { return slotNum; }
	bool getIsOccupied() { return isOccupied; }
	string getVehicleNumber() { return vehicleNum; }
	string getVehicleType() { return vehicleType; }
	int getEntryTime() { return entryTime; }
	int getExitTime() { return exitTime; }
};
class ParkingLot {
private: //changed to private bcz they can only be accessed by admin, not by the user
	int TotalParkingSlots;
	int PricePerHour;
	float RevenueGenerated;
	parkingSlot* slots; //dynamic slot allocation
public:
	ParkingLot() { //dc
		TotalParkingSlots = 0;
		PricePerHour = 60;
		RevenueGenerated = 0.00;
		slots = nullptr;
	}
	void initialiseSlots(int total) { //dynamic allocation of slots in main
		TotalParkingSlots = total;
		slots = new parkingSlot[TotalParkingSlots];
		for (int i = 0; i < TotalParkingSlots; i++) {
			slots[i].setSlot(i + 1);  // slots numbered 1, 2, 3
		}
		cout << endl;
		cout << TotalParkingSlots << " parking slots created successfully!" << endl;
	}
	//getters and setters
	int getTotalSlots() { return TotalParkingSlots; }
	int getPricePerHour() { return PricePerHour; }
	double getRevenueGenerated() { return RevenueGenerated; }
	void SetPricePerHour(int p) { PricePerHour = p; }
	void addRevenue(double amount) { 
		RevenueGenerated += amount;
	}
	//give access of slot array to admin (getter)
	parkingSlot* getSlots() { return slots; }
	//dynamic memory deallocation
	~ParkingLot() { 
		if (slots != nullptr) {
			delete[] slots;
		}
	}
};
class User { //taken from main to implement Admin class
protected:
	string NameOfUser;
	string PasswordOfUser;
public:
	User() {
		NameOfUser = "No Name";
		PasswordOfUser = "No Password";
	}
	void SetData(string u, string p) {
		NameOfUser = u; 
		PasswordOfUser = p;
	}
	string GetNameOfUser() {
		return NameOfUser;
	}
	string GetPasswordOfUser() {
		return PasswordOfUser;
	}
};
class Admin : public User {
public:
	Admin() { //dc
	}
	bool adminLogin() {
		string name, password;
		cout << "Username : ";
		cin >> name;
		cout << "Password : ";
		cin >> password;
		//read stored credentials from file first
		//COMPARE entered username and password with info stored in file
		ifstream file("AdminCredentials.txt");
		if (!file.is_open()) { //username doesnt match with stored username = account not found
			cout << "\nNo admin account found. Please sign up first!" << endl;
			return false;
		}
		string storedName, storedPassword;
		//login successful if entered username and password match with stored info
		while (file >> storedName >> storedPassword) {
			if (storedName == name && storedPassword == password) {
				file.close();
				NameOfUser = storedName;
				PasswordOfUser = storedPassword;
				cout << "\nLogin Successful! Welcome, " << NameOfUser << "!" << endl;
				return true;
			}
		}
		file.close();
		cout << "\nIncorrect Username or Password!" << endl;
		return false;
	}
	void adminSignUp() {
		string newName, newPassword;
		cout << "Enter Your Username : ";
		cin >> newName;
		cout << "Enter Your Password : ";
		cin >> newPassword;
		//check if username already exists
		ifstream checkFile("AdminCredentials.txt");
		if (checkFile.is_open()) {
			string n, p;
			while (checkFile >> n >> p) {
				if (n == newName) {
					cout << "\nUsername already exists. Please choose a different one!" << endl;
					checkFile.close();
					return;
				}
			}
			checkFile.close();
		}
		//save admin info to file
		ofstream file("AdminCredentials.txt", ios::app);
		if (!file.is_open()) {
			cout << "\nError opening file." << endl;
			return;
		}
		file << newName << " " << newPassword << endl;
		file.close();
		cout << "\nAdmin account created successfully!" << endl;
	}
	void deleteAdminAccount() {
		string delChoice;
		cout << "\nDo you permanently want to delete '" << NameOfUser << "' account? ";
		cin >> delChoice;
		if (delChoice != "yes") {
			cout << "Deletion cancelled!" << endl;
			return;
		}
		ifstream inFile("AdminCredentials.txt");
		ofstream tempFile("temp.txt");
		//check if file actually exists
		if (!inFile) {
			cout << "Error: Could not open credentials file." << endl;
			return;
		}
		string n, p;
		bool found = false;
		//read every name and password from the file
		while (inFile >> n >> p) {
			//if this name is NOT the current user, copy them to the new file
			if (n != NameOfUser) {
				tempFile << n << " " << p << endl;
			}
			else {
				//stop if name MATCHES and dont write in tempfile, deletes the user bcz he is not written in new tempFile
				found = true;
			}
		}
		inFile.close();
		tempFile.close();
		//replace the old file with new ones
		remove("AdminCredentials.txt");//del old file     
		rename("temp.txt", "AdminCredentials.txt");//rename temp.txt to the original name
		
		if (found) {
			cout << "Account deleted successfully. Logging out..." << endl;
		}
		else {
			cout << "Account record not found in file..." << endl;
		}
	}
void settParkingLot(ParkingLot& setLot) {
	int total;
	cout << "Enter Total Number of Parking Slots : ";
	cin >> total;
	if (total <= 0) {
		cout << "\nInvalid Input. Please enter a positive value!" << endl;
		return;
	}
	setLot.initialiseSlots(total); //func inside ParkingLot class, it will dynamically allocate the no. of slots entered by admin.
}
void displayParkingSlots(ParkingLot& viewLot) {
	cout << "\n========== PARKING SLOT STATUS ==========\n";
	if (viewLot.getTotalSlots() == 0) { //if admin hasn't initialized any slots
		cout << "No slots initialised yet..." << endl;
		return;
	}
	//display information table
	cout << left << setw(8) << "Slot" << setw(12) << "Status" << setw(18) << "Vehicle No." << setw(12) << "Type" << setw(12) << "Entry Time" << endl;
	for (int i = 0; i < 60; i++) cout << "-";
	cout << endl;
	parkingSlot* slots = viewLot.getSlots(); //dynamically initialize no. of slots entered
	//slot occupation logic
	int occupied = 0;
	int available = 0;
	for (int i = 0; i < viewLot.getTotalSlots(); i++) {
		cout << left << setw(8) << slots[i].getSlotNum();
		if (slots[i].getIsOccupied()) {
			occupied++;
			cout << setw(12) << "OCCUPIED" << setw(18) << slots[i].getVehicleNumber() << setw(12) << slots[i].getVehicleType() << setw(12) << slots[i].getEntryTime();
		}
		else {
			available++;
			cout << setw(12) << "FREE" << setw(18) << "---" << setw(12) << "---" << setw(12) << "---";
		}
		cout << endl;
	}
	for (int i = 0; i < 60; i++) cout << "-";
	cout << endl;
    //display final information below the table	
	cout << "Total Slots : " << viewLot.getTotalSlots() << "  |  Occupied : " << occupied << "  |  Available : " << available << endl;
}
void displayRevenue(ParkingLot& lotRev) {
	cout << "\n========== REVENUE REPORT ==========\n"; 
	//accessing through getter functions from class ParkingLot
	cout << "Current Hourly Rate: Rs. " << lotRev.getPricePerHour() << " / hour" << endl;
	cout << "Total Revenue Earned: Rs. " << fixed << setprecision(2) << lotRev.getRevenueGenerated() << endl;
}
void updateRate(ParkingLot& lotRate){
int newRate;
	cout<<"\n====CHANGE HOURLY PARKING RATE===="<<endl;
	//access current rate through getter 
	cout<<"Current Hourly Rate: Rs. "<<lotRate.getPricePerHour()<<" /hour "<<endl;
	cout<<"Enter New Rate: ";
	cin>>newRate;
	if(newRate<=0){
		cout<<"Invalid Rate. Please enter a positive value!"<<endl;
        return;
	}
	lotRate.SetPricePerHour(newRate); //updates price through class ParkingLot
	cout<<"Hourly Rate Updated to: Rs. "<<newRate<<" /hour successfully! "<<endl;
	cout<<"All future checkouts will use this rate!"<<endl;
}
};
