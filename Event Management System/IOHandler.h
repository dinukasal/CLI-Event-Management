#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <conio.h> //_getch() fn
#include <Windows.h>
#include <cstdlib>
#include "UserHandler.h"
#include "HallHandler.h"
#include "TicketHandler.h"
#include "Database.h"

#ifndef EVENT_HANDLER
	#include "EventHandler.h"
#endif // 0

using namespace std;

class IOHandler {
private:
	UserHandler* users;
	EventHandler *eventhandler;
	HallHandler *hallhandler;
	bool isloggedIn;
	TicketsHandler* ticketshandler;
	
public:
	IOHandler(UserHandler*,EventHandler*,HallHandler*,TicketsHandler*);
	void displayMenu(int number);
	void login(char choice);
	void getInput();
	void displayAdminMenu();
	void displayCustomerMenu();
	char getCharInput(int choices); // get an input
	void setLoggedIn();	
};

#endif