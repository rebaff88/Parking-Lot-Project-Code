// this is the code for user and admin login ,signup and delete operations for the account
// main function will be implemented later as a whole when the whole logic is done 


# include <iostream>
# include <string>
# include <fstream>


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

// login for the user
	static string loginUser(string uname, string pwd) {

		ifstream file("users.txt");


		string u, p, r;

// same format as above 
		while (getline(file, u, ',')) {

			getline(file, p, ',');
			getline(file, r);

// if user name and password match , access is granted
			if (u == uname &&  p == pwd) {

				file.close();

				return r;

			}

			

		}

		file.close();

		// return nothing when either one of username and password is incorrect
		return "";


	}
// tricky here , deleting the account
	static bool deleteUser(string uname, string pwd) {


		ifstream file("users.txt");
		ofstream temp("temp.txt"); // clone file implemented here


		string u, p, r;

		bool found = false;
// same format as above
		while (getline(file, u, ',')) {
			getline(file, p, ',');
			getline(file, r);
// except the account which is to be deleted all the rest of data is written in temp file
			if (u == uname && p == pwd) {

				found = true;
			}

			else {

				temp << u << "," << p << "," << r << endl;
			}



		}

		file.close();
		temp.close();

// removing orginal file
	
	remove("users.txt");
//	renaming the new file as "user.txt"	
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
int main() {

}
