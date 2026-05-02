#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User {
protected:
    string username;
    string password;
    string role;      //admin or customer
public:
    User();
    User(const string& uname, const string& pwd, const string& r);
    //getters
    string getUsername() const;
    string getPassword() const;
    string getRole() const;
    //setters
    void setUsername(const string& u);
    void setPassword(const string& p);
    //pure virtual: each role displays menu differently
    virtual void showMenu() = 0;
    //for file storage
    string serialize() const;   // username,password,role
    bool   matchCredentials(const string& uname, const string& pwd) const;
    virtual ~User() {}
};
//derived from user class
class Admin : public User {
public:
    Admin();
    Admin(const string& uname, const string& pwd);
    void showMenu() override;
};
//derived from user class
class Customer : public User {
public:
    Customer();
    Customer(const string& uname, const string& pwd);
    void showMenu() override;
};
#endif // USER_H
