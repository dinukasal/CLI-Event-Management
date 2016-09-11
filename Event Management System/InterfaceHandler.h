#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <conio.h> //_getch() fn
#include <Windows.h>
#include <cstdlib>
#include "Users.h"
#include "HallHandler.h"
#include "TicketHandler.h"
#include "Files.h"

#ifndef EVENT_HANDLER
	#include "EventHandler.h"
#endif // 0

using namespace std;

class InterfaceHandler {
private:
	UserHandler* users;
	EventHandler *eventhandler;
	HallHandler *hallhandler;
	bool isloggedIn;
	TicketsHandler* ticketshandler;
	
public:
	InterfaceHandler(UserHandler*,EventHandler*,HallHandler*,TicketsHandler*);
	void displayMenu(int number);
	void login(char choice);
	void getInput();
	void displayAdminMenu();
	void displayCustomerMenu();
	char getCharInput(int choices); // get an input
	void setLoggedIn();	
};

#endif