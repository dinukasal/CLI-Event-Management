#ifndef TICKET_HANDLER
#define TICKET_HANDLER

#include "DataHandler.h"
#include <vector>
#include "UserHandler.h"

class TicketsHandler {
private:
	DataHandler datahandler;
	vector<int> tickets_per_event;
	UserHandler *userhandler;
public:
	TicketsHandler(UserHandler* userhandler);
	void printVector(vector <vector<int>>); //print any 2d vector
	void printSoldTickets();
	void removeTicket(int eventNumber); // remove the ticket in the ticket_file
	void reloadTickets();
	void addTicket(int eventNo);
	void printAvailableTickets();
	void buyTicket(int eventNo,int amount);
	void cancelTicket(int eventNo,int count);
};

#endif