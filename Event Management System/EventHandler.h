#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <iostream>
#include <fstream>
#include <iostream>
#include "HallHandler.h"
#include "TicketHandler.h"

#include "DataHandler.h"

using namespace std;

struct Event {
	string date;
	string time;
	string name;
	string venue;
};

class EventHandler {
private:
	Event event;
	Event eventsarray[150];
	DataHandler datahandler;
	int eventscount ;
	bool firstTimeCount;
	bool dataLoaded = false;
	HallHandler* hallhandler;
	TicketsHandler* tickets;
public:
	EventHandler(HallHandler* hallmanager,TicketsHandler* tickets);
	Event* getEvents();
	int getEventsCount();
	void addEvent(string name, string date, string time, string hall,bool writeTickets);
	void removeEvent(int eventNo);
	void writeEvents();// write current events in the memory to the file
	void reloadEvents();
	bool deleteAllEvents();
};
#endif