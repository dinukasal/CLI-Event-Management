#include "Users.h"

UserHandler::UserHandler() {
	adminCount = 0;
	customerCount = 0;
}

void UserHandler::addUsers(string * dataset, int length, User* userSet, int userType)
{
	User user;
	User * users;
	string line;
	for (int i = 0;i <length;i++) {
		line = *(dataset + i);
		user.name = line.substr(0, line.find(" "));
		user.password = line.substr(line.find(" ") + 1);
		*(userSet + i) = user;
		if (userType == 1) {
			adminCount++;
		}
		else {
			customerCount++;
		}
	}
}
void UserHandler::getAdmins(string * dataset,int count)
{
	addUsers(dataset,count,adminsarray,1);
}

void UserHandler::getCustomers(string * dataset,int count)
{
	addUsers(dataset,count,customersarray,2);
}

bool UserHandler::checkAdmin(string username, string password)
{
	return checkUser(username, password,1);
}
bool UserHandler::checkCustomer(string username, string password)
{
	return checkUser(username, password, 2);
}

bool UserHandler::checkUser(string username,string password,int userType) {
	if (userType == 1) {	//user type admin
		for (int i = 0;i < adminCount;i++) {
			//cout << (admin[i].name==username) << endl;
			if (adminsarray[i].name == username && adminsarray[i].password == password) {
				//cout << password << endl;

				return true;
			}
		}
	}
	else {
		for (int i = 0;i < customerCount;i++) {
			if (customersarray[i].name == username && customersarray[i].password == password) {
				return true;
			}
		}
	}
	return false;
}

int UserHandler::getCount(int userType) {
	if (userType == 1) {
		return adminCount;
	}
	else {
		return customerCount;
	}
}