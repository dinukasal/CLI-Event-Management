#include "TicketHandler.h"

TicketsHandler::TicketsHandler() {
	vector <string> data = datahandler.getLines(ticket_file);
	ticketsvector.clear();

	for (int i = 0; i < data.size(); i++)
	{
			for (int j = 0; j < data[i].size(); j++) {
				if (data[i][j] == '-') {
					ticketsvector.push_back(stoi(data[i].substr(j+1, data[i].size() - j)));
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
	cout << "-------------" << endl;
	for (int i = 0; i < ticketsvector.size(); i++)
	{
		cout << "Event " << i +1<< " >> Sold Count: "<< ticketsvector[i]<<endl;
	}
}

void TicketsHandler::removeTicket(int eventNumber)
{
	ticketsvector.erase(ticketsvector.begin()+ eventNumber);
	datahandler.clearFile(ticket_file);
	string data="";
	for (int i = 0; i < ticketsvector.size(); i++)
	{
		data += to_string(i + 1) + "-" + to_string(ticketsvector[i])+"\n";
	}
	cout << "Writing data to ticket file\n" << data << endl;
	datahandler.writeFile(ticket_file, data);
	reloadTickets();
}

void TicketsHandler::reloadTickets()
{
	vector <string> data = datahandler.getLines(ticket_file);
	ticketsvector.clear();
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == '-') {
				ticketsvector.push_back(stoi(data[i].substr(j + 1, data[i].size() - j)));
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
	cout <<         "-----------------" << endl;
	for (int i = 0; i < ticketsvector.size(); i++)
	{
		cout << "Event " << i + 1 << "  " << ticketsvector[i]<<" sold" << endl;
	}
}

void TicketsHandler::buyTicket(int eventNo,int amount)
{
	ticketsvector[eventNo] += amount;
	datahandler.clearFile(ticket_file);
	string data = "";
	for (int i = 0; i < ticketsvector.size(); i++)
	{
		data += to_string(i + 1) + "-" + to_string(ticketsvector[i]) + "\n";
	}
	cout << "Writing data to ticket file\n" << data << endl;
	datahandler.writeFile(ticket_file, data);
	reloadTickets();
}

