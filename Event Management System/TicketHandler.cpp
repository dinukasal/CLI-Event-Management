#include "TicketHandler.h"

TicketsHandler::TicketsHandler(UserHandler *userhandler) {
	TicketsHandler::userhandler = userhandler;
	vector <string> data = datahandler.getLines(ticket_file);
	tickets_per_event.clear();

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == '-') {
				tickets_per_event.push_back(stoi(data[i].substr(j + 1, data[i].size() - j)));
			}
		}
	}
}

void TicketsHandler::printVector(vector <vector<int>> data) {
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j <data[i].size(); j++) {
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
}

void TicketsHandler::printSoldTickets()
{
	cout << endl << "Sold Tickets" << endl;
	cout         << "============" << endl;
	for (int i = 0; i < tickets_per_event.size(); i++)
	{
		cout << "Event " << i +1<< " >> Sold Count: "<< tickets_per_event[i]<<endl;
	}
}

void TicketsHandler::removeTicket(int eventNumber)
{
	tickets_per_event.erase(tickets_per_event.begin()+ eventNumber);
	datahandler.clearFile(ticket_file);
	string data="";
	for (int i = 0; i < tickets_per_event.size(); i++)
	{
		data += to_string(i + 1) + "-" + to_string(tickets_per_event[i])+"\n";
	}
	datahandler.writeFile(ticket_file, data);
	reloadTickets();
}

void TicketsHandler::reloadTickets()
{
	vector <string> data = datahandler.getLines(ticket_file);
	tickets_per_event.clear();
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == '-') {
				tickets_per_event.push_back(stoi(data[i].substr(j + 1, data[i].size() - j)));
			}
		}
	}
}

void TicketsHandler::addTicket(int eventNo)
{
	datahandler.appendToFile(ticket_file, to_string(eventNo) + "-0\n");
	reloadTickets();
}

void TicketsHandler::printAvailableTickets()
{
	cout << endl << "Available Tickets" << endl;
	cout <<         "=================" << endl;
	for (int i = 0; i < tickets_per_event.size(); i++)
	{
		cout << "Event " << i + 1 << "  " << tickets_per_event[i]<<" sold" << endl;
	}
}

void TicketsHandler::buyTicket(int eventNo,int amount)
{
	tickets_per_event[eventNo] += amount;
	datahandler.clearFile(ticket_file);
	string data = "";
	for (int i = 0; i < tickets_per_event.size(); i++)
	{
		data += to_string(i + 1) + "-" + to_string(tickets_per_event[i]) + "\n";
	}
	datahandler.writeFile(ticket_file, data);
	reloadTickets();
}

void TicketsHandler::cancelTicket(int eventNo,int count)
{
	tickets_per_event[eventNo]-=count;
	datahandler.clearFile(ticket_file);

	for (int i = 0; i < tickets_per_event.size(); i++) {
		datahandler.appendToFile(events_file,to_string(tickets_per_event[i]));
	}

}

