#include "EventHandler.h"

EventHandler::EventHandler(HallHandler* hallhandler,TicketsHandler* tickets)
{
	event.date = "";
	event.name = "";
	event.time = "";
	event.venue = "";
	eventscount = 0;
	EventHandler::tickets = tickets;
}

Event * EventHandler::getEvents()
{
	if (dataLoaded == false) {
		eventscount = 0;
		int linecount = 1;
		string* dataset = datahandler.fetchData(events_file, &linecount);

		int linePattern = 0;
		int eventNo = 0;

		for (int j = 0; j < linecount; j++)
		{
			if (string(*(dataset + j)) != "") {

				switch (linePattern)
				{
				case 0:
					eventsarray[eventNo].date = string(*(dataset + j));
					eventscount++;
					break;
				case 1:
					eventsarray[eventNo].time = string(*(dataset + j));
					break;
				case 2:
					eventsarray[eventNo].name = string(*(dataset + j));
					break;
				case 3:
					eventsarray[eventNo++].venue = string(*(dataset + j));
					break;
				}

				linePattern++;
			}
			else {
				linePattern = 0;
			}
		}

		firstTimeCount = false;
		dataLoaded = true;
	}
		cout << endl;
		for (int i = 0; i < eventscount; i++)
		{
			cout << "Event "<<i+1<<": " << eventsarray[i].name << endl;
			cout << "Date : "<<eventsarray[i].date << endl;
			cout << "Time : "<<eventsarray[i].time << endl;
			cout << "Hall : " << eventsarray[i].venue << endl << endl;
		}
	return nullptr;
}

int EventHandler::getEventsCount() {
	return eventscount;
}

void EventHandler::addEvent(string name, string date, string time, string hall,bool writeTickets)
{
	if (date != "" && name != "" && time != "" && hall != "") {
		datahandler.appendToFile(events_file, "\n\n" + date + '\n' + time + '\n' + name + '\n' + hall);
		if (writeTickets == true) {
			tickets->addTicket(eventscount + 1);
		}
	}
	else {
		cout << "Event adding failed" << endl;
	}
	reloadEvents();
}

void EventHandler::removeEvent(int eventNo){
	eventNo--;
	hallhandler->unreserveHall(eventsarray[eventNo].venue);
	eventsarray[eventNo].date = "";
	eventsarray[eventNo].name = "";
	eventsarray[eventNo].time = "";
	eventsarray[eventNo].venue = "";

	datahandler.clearFile(events_file);
	
	tickets->removeTicket(eventNo);
	writeEvents();
	reloadEvents();

}

void EventHandler::writeEvents()
{
	for (int i = 0; i < eventscount; i++) {
		addEvent(eventsarray[i].date, eventsarray[i].time, eventsarray[i].name, eventsarray[i].venue,false);
	}
}

void EventHandler::reloadEvents()
{
	dataLoaded = false;
}

bool EventHandler::deleteAllEvents()
{
	if (eventscount > 0) {
		datahandler.clearFile(events_file);
		datahandler.clearFile(reservations_file);
		datahandler.clearFile(ticket_file);
		reloadEvents();
		tickets->reloadTickets();
		hallhandler->reloadhalls();
		return true;
	}
	else {
		return false;
	}
}
