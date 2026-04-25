#include<iostream>
#include<fstream>//this library will handle file handling
#include<string>//library for string which will help to  //access functions of strings 
using namespace std;
// starting with the user class:
class User {
	//data members will be protected:
protected:
	//this is going to have two data members:
	string UserName;
	string UserPassword;//i have used string so that; the user
	//can eneter both letters and numbers.
public:
	//now i am going to create the functions, constructers:
	User() {
		UserName = "No Name";
		UserPassword = "No Password";
	}
	//creating a setter function
	void SetData(string u, string p) {
		UserName = u;//setting the values of the data members 
		UserPassword = p;
	}
	string GetNameOfUser() {
		//creating agetter function so that the desired value
		//will get returned:
		return UserName;
	}
	string GetPasswordOfUser() {
		//now creating a getter function for the password of the user:
		return UserPassword;
	}
};
//now here i am going to create some of the functions regarding the 
//various functions related to the user interface :
class Admin : public  User {
	//now here admin is a derived class:
public:
	void ShowTheRole() {
		cout << "You Have Been Logged In As An Admin!" << endl;
	//admin class
	}
};
class Customer : public User {
public:
	void ShowTheRole() {
		cout << "You Have Been Logged In As An Customer!" << endl;
		//Customer class
	}
};
void SignUpFunction() {
	//this function will work on the signup, done:
	string NameOfTheUser;
	string PasswordOfUser;
	string RoleOfTheUser;//whether he is a client or admin;
	cout << "For SignUp:" << endl;
	cout << "Please Enter Your Name : " << endl;
	cin.ignore(); 
	getline(cin, NameOfTheUser);//will take name and even full name
	cout << "Please Enter Your Password" << endl;
	cin >> PasswordOfUser;
	if (PasswordOfUser.length() < 4) {
		cout << "Password Must Be Comprised of At Least 4 Characters!" << endl;
		cout << "Input Password Again " << endl;
		return;
	}
	cout << "From Below Select a Numeral Representing  Your Role: " << endl;
	cout << 1 << " . Admin" << endl;
	cout << 2 << " . Customer" << endl;
	cin >> RoleOfTheUser;//inputs so that what kind of role be
	//selected by the user, will further be used
	//in other functions as welll
	//now we just need to create a file which is going to store 
	//the every data and made it as a record for every user
	//heere i am going to use file handling so :
	ofstream file("RecordOfUserData.txt", ios::app);
	if (!file) {
		cout << "Error opening file!" << endl;
		return;
	}
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
	cin.ignore();
	getline(cin, NewNameOfUser);
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
	TheCurrentUserName = "";
	TheCurrentUserPassword = "";
	TheCurrentUserRole = "";
	//simply assigned new values:
	cout << "LogOut has Performed Successfully!" << endl;
	//data is not remoeved just assined new values
}
//now what if the user wants to delete his account
//for this purpose:
void DeleteTheUserAccount(string& TheCurrentUser) {
	//here if the user a s a whole gets deleted:
	//for this we first have to access and write into the file:
	ifstream file("RecordOfUserData.txt");
	//this is the orignal file which will get opened:
	ofstream temp("TempFileForUserData.txt");//a temporary file here is created
	//now i am going to set up  LOOP WHICH IS 
	//GOING TO CHECK WHERE THE PERSONS USER NAME AND DATA Lies:
	//for this purpose:
	string checkUser;
	string checkPassword;
	string checkRole;
	bool foundData = false;
	while (file >> checkUser >> checkPassword >> checkRole) {
		//now using a conditional to check the vulnebilities:
		if (checkUser != TheCurrentUser) {
			//means there is no match so move onwards:
			temp << checkUser << " " << checkPassword << " " << checkRole << endl;
			//the data will get writted in the same format as the 
			//orignal file was written in to 
		}
		else {
			foundData = true;//data is found and not written in the new file
			//as we are going to delete the account so we are not 
			//writing it in the new file
		}
	}
	//now as we opened the files first now closing 
	file.close();
	temp.close();
	//the new file enholding the data :
	(void)remove("RecordOfUserData.txt");//removing the orignal file
	(void)rename("TempFileForUserData.txt", "RecordOfUserData.txt");//renaming the new file to the orignal file name)
	//everytime the user deletes an account the data will get 
	//copied and again goes copied in the temp file and the names are interchanged
	//and the orignal file is removed and the new file is renamed to the orignal file name, so that the data is not lost but the user account is deleted
	//void is used for acceseing compiler warning as the remove and rename functions return an int value but we are not using it so to avoid the warning we have used void
	cout << "Account Has Been Deleted Successfully!" << endl;
}
int main() { 
	int ChoiceOfUser=0;//initializing and declaring
	string RoleOfUser;
	string NameOfUser;
	string PasswordOfUser;
	//now implementing the already created functions :
	cout << "1 . Sign-Up  " << endl;
	cout << "2 . Log-In  " << endl;
	cout << "3 . Delete Account  " << endl;
	cout << "4 . Logout" << endl;
	cout << "5 . Exit  " << endl;
	//loop:
	while (true) {//loop will run continuosly
		cout << "Please Input Your Choice : " << endl;
		cin >> ChoiceOfUser;
		//first lets give a check so that choice is valid:
		if (ChoiceOfUser < 1 || ChoiceOfUser>5) {
			cout << "Invalid Choice!" << endl;
			cout << "PLease Input Between 1 and 4" << endl;
			continue;//loop will be continued
		}
		if (ChoiceOfUser == 1) {
			//simply signin function will get:
			SignUpFunction();
		}
		else if (ChoiceOfUser == 2) {
			//now checking what is the role of the user:
			if (UserLogin(RoleOfUser, NameOfUser, PasswordOfUser) ){
				cout << "Log-In has Been Performed Successfully!" << endl;
				if (RoleOfUser == "Admin"||RoleOfUser =="admin") {
					Admin AdminUser;//an object of admin lass has
					//been creatyed
					AdminUser.ShowTheRole();
				}//otherwise the object of customer will be created:
				else if (RoleOfUser == "Customer" || RoleOfUser == "customer"){
					Customer CustomerUser;
					CustomerUser.ShowTheRole();
				}
			}
		}
		//now for the next possibilty of Choice :
		else if (ChoiceOfUser == 3) {
			//the user has selected to delete the account:
			cout << "Enter Your UserName to Delete Your Account: " << endl;
			cin >> NameOfUser;
			DeleteTheUserAccount(NameOfUser);//funtion called and parameter has beeen 
			//passed in it 
		}
		else if (ChoiceOfUser == 4) {
			UserLogOut(RoleOfUser, NameOfUser, PasswordOfUser);
		}
		//now for the exit::
		else if (ChoiceOfUser == 5) {
			cout << "Program Has Been Exited Successfully!" << endl;
			break;//adding break to stop the loop and exit
		}
	}
	return 0;
}

