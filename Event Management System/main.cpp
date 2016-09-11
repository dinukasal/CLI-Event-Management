#include "DataHandler.h"
#include "Users.h"
#include <conio.h>
#include "IOHandler.h"
#include "EventHandler.h"
#include "HallHandler.h"
#include "Database.h"

using namespace std;

int main() {
	DataHandler datahandler;
	UserHandler users;
	string *dataset;
	HallHandler hallhandler;
	TicketsHandler tickets;
	EventHandler eventhandler = EventHandler(&hallhandler,&tickets);
	IOHandler io = IOHandler(&users, &eventhandler, &hallhandler,&tickets);

	int dataCount = 0;

	if (!datahandler.checkFiles())
		cout << "Error loading the required text files.\nPlease Check" << endl;

	dataset = datahandler.fetchData(admin_file, &dataCount);
	users.getAdmins(dataset, dataCount);

	dataset = datahandler.fetchData(customers_file, &dataCount);
	users.getCustomers(dataset, dataCount);

	io.displayMenu(0);	
	cin.get();
	return 0;

}