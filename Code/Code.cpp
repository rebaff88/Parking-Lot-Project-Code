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
	cout << "For SignUp:" << endl;
	cout << "Please Enter Your Name : " << endl;
	cin >> NameOfTheUser;//input taken
	cout << "Please Enter Your Password" << endl;
	cout << "From Below Select Your Role: " << endl;
	cout << 1. << "Admin" << endl;
	cout << 2. << "Customer" << endl;
	cin >> RoleOfTheUser;//inputs so that what kind of role be
	//selected by the user, will further be used
	//in other functions as welll
	//now we just need to create a file which is going to store 
	//the every data and made it as a record for every user
	//heere i am going to use file handling so :
	ofstream file("RecordOfUserData.txt", ios::app);
	//here i ahve used append, as by this the already recorded
	//will not get overwritted and the new data will
	//stored at the end of the file 
	//now i am going to arrange the sequence to according which 
	//the data will get store :
	file << NameOfTheUser << " " << PasswordOfUser << " " << RoleOfTheUser << endl;
	//now ia hve stored it in a sequence so now i am going
	//to close the file :
	file.close();
	cout << endl;
	cout << "The SignUp has Been Done Succesfully!" << endl;
}
//now for the Login function : 
//now login will match with the alredy present datya 
//stored in the file with the new one :
bool UserLogin(string& TheCurrentUserRole, string& TheCurrentUserName, string& TheCurrentUserPassword) {
	//role-nme-password arr passed:
	string r;
	string u;
	string p;//local varibales for equalling
	//now taking the input to compare with the 
	//prevos data:
	string NewNameOfUser;//tghe name which is going to gat compare
	//with the already pesent data in the file :
	string NewPasswordOfUser;//the password which is going to get compare
	cout << "  For LogIn : " << endl;
	cout << "Please Enter Your Name : " << endl; 
		cin >> NewNameOfUser;
		cout << "Please Enter Your Password : " << endl;
		cin >> NewPasswordOfUser;
		//till here inputs for login are taken 
		//now what ia ma goig to do is simply compare them :
		//now opening and readiing the file contents:\
		
		bool UserDoExists = false;//this is going to check whether the user exists or not
		ifstream file("RecordOfUserData.txt");
		while (file >> u >> p >> r) {
			//as in the file we have stroed the dta in this format :
			//name paswrd role, >>: will consider space as seperation
			//now apllying a conditional to check :
			if (u == NewNameOfUser) {
				UserDoExists = true;//name is found
				if(p == NewPasswordOfUser) {//pswrd found
					//here we are simply first checkin the priority conditionals:
					TheCurrentUserName = u;
					TheCurrentUserPassword = p;
					TheCurrentUserRole = r;//simply assigning the values
					//which were initialy passed as the parameters:
					return true;//conditional true , move to next
			    }
			}
		}
		if (UserDoExists) {//ie is false
			cout << "Incorrect Password," << endl;
			cout << "Please Try Again!" << endl;
		}
		else {//no login is done , has to sign up first
			cout << "User Not Found In Records" << endl;
		}
		return false;//if not found
}
//now for logout:
void UserLogOut(string& TheCurrentUserRole, string& TheCurrentUserName, string& TheCurrentUserPassword) {
	//simply iam just going to reset the data or empty it:
	TheCurrentUserName = " ";
	TheCurrentUserPassword = " ";
	TheCurrentUserRole = " ";
	//simply assigned new values:
	cout << "LogOut has Performed Successfully!" << endl;
	//data is not remoeved just assined new values
}
//now what if the user wants to delete his account
//for this purpose:
void DeleteTheUserAccount(string& TheCurrentUser) {
	//here if the user a s a whole gets deleted:
	//for this we first have to access and write into the file:
	ifstream file("RecordOfTheUserData.txt");
	//this is the orignal file which will get opened:
	ofstream temp("TempFileForUserData.txt");//a temporary file here is created
	//now i am going to set up  LOOP WHICH IS 
	//GOING TO CHECK WHERE THE PERSONS USER NAME AND DATA Lies:
	//for this purpose:
	string checkUser;
	string checkPassword;
	string checkRole;
	while (file >> checkUser >> checkPassword >> checkRole) {
		//now using a conditional to check the vulnebilities:
		if (checkUser != TheCurrentUser) {
			//means there is no match so move onwards:
			temp << checkUser << " " << checkPassword << " " << checkRole << endl;
			//the data will get writted in the same format as the 
			//orignal file was written in to 
		}
	}
	//now as we opened the files first now closing 
	file.close();
	temp.close();
	//the new file enholding the data :
	remove("RecordOfTheUserData.txt");//removing the orignal file
	rename("TempFileForUserData.txt", "RecordOfTheUserData.txt");//renaming the new file to the orignal file name)
	//everytime the user deletes an account the data will get 
	//copied and again goes copied in the temp file and the names are interchanged
	//and the orignal file is removed and the new file is renamed to the orignal file name, so that the data is not lost but the user account is deleted
}
int main() { 
	//creating a parkinglott object:
	//ParkingLot p1;
	return 0;
}