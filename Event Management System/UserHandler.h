#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

struct User {
	string name;
	string password;
};

class UserHandler {
private:
	User adminsarray[10];
	int adminCount;
	User customersarray[500];
	int customerCount;
	int loggedUser;
public:
	UserHandler();
	void getAdmins(string *,int);
	void getCustomers(string *,int);
	bool checkAdmin(string username,string password);
	bool checkCustomer(string username,string password);
	bool checkUser(string username, string password, int userType);
	int getCount(int userType);
	void addUsers(string * dataset,int length,User* userSet,int userType);
	int getLoggedUser();
};

#endif // 
