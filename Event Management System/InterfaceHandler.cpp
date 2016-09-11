#include "InterfaceHandler.h"

InterfaceHandler::InterfaceHandler(UserHandler* outerUsers,EventHandler* eventhandler,HallHandler* hallhandler, TicketsHandler* tickets) {
	users= outerUsers;
	InterfaceHandler::eventhandler = eventhandler;
	InterfaceHandler::hallhandler = hallhandler;
	isloggedIn = false;
	InterfaceHandler::ticketshandler = tickets;
}

void InterfaceHandler::displayMenu(int number)
{
	char choice = 0;
	switch (number) {
	case 0:
		cout << "Event System" << endl;
		cout << "============" << endl << endl;
		cout << "1: View Events" << endl;
		cout << "2: Login Administrator" << endl;
		cout << "3: Login Customer" << endl;
		cout << "press q to exit" << endl;
		cout << "press b to go back" << endl;
		cout << endl;

		getInput();

		break;
	case 1:
		displayAdminMenu();
		break;
	case 2:
		setLoggedIn();
		displayCustomerMenu();
		break;
	}
}

void InterfaceHandler::getInput()
{
	char choice = 0;
	while (true) {
		choice = _getch();	// from conio.h file
		if (choice == '1' || choice == '2' || choice == '3' || choice == 'q' || choice == 'b') {
			break;
		}
		else {
			cout << "please enter correct number!" << endl;
		}
	}

	if (isdigit(choice) && (choice == '2' || choice == '3')) {
		login(choice);
	}
	else if (choice == '1') { // key --> 3
							  //display events
		eventhandler->getEvents();
		displayMenu(0);
	}
	else if (choice == 113) {
		exit(0);
	}

}

void InterfaceHandler::login(char choice)
{
	string username;
	string password;

	if (isdigit(choice)) {

		switch (choice) {
		case '2':
			cout << "Administrator login" << endl;
			cout << "===================" << endl;
			cout << "Username:";
			cin >> username;
			//getline(cin, username);
			//username = cin.get();
			cout << "Passsword:";
			//getline(cin, username);
			cin >> password;

			//password = getPassword();

			if (users->checkUser(username, password, 1)) {
				cout << endl<<"logged in!" << endl;
				isloggedIn = true;
				displayAdminMenu();

			}
			else {
				cout << endl<<"wrong password or username" << endl;
				displayMenu(0);
			}

			break;
		case '3':
			cout << "Customer login" << endl;
			cout << "=============" << endl;
			cout << "Username:";
			getline(cin, username);
			cout << "Password:";

			//password = getPassword();

			getline(cin, password);

			if (users->checkUser(username, password, 2)) {
				cout << endl<<"logged in!" << endl;
				isloggedIn = true;
				displayCustomerMenu();
			}
			else {
				cout <<endl <<"wrong password or username" << endl;
				displayMenu(0);
			}

			break;
		}
	}
	else {
		login(choice);
	}
}

void InterfaceHandler::displayAdminMenu()
{
	cout << endl <<"Administrator Dashboard" << endl;
	cout << "==============" << endl;

	cout << "1: Manage Events " << endl;
	cout << "2: Manage Halls" << endl;
	cout << "3: View Events" << endl;
	cout << "4: View Sold Tickets" << endl;

	cout << "q: Quit" << endl;

	char choice = getCharInput(4);

	if (choice == '1') {
		eventhandler->getEvents();
		ticketshandler->printSoldTickets();

		cout << endl;
		cout << "1: Create an event" << endl;
		cout << "2: Delete an event" << endl;
		cout << "3: Delete All events" << endl;

		char choice = getCharInput(3);

		if (choice == '1') {
			cout << "Enter Event Name: ";
			string name;
			//cin.get();
			getline(cin, name);

			string date;
			cout << "Enter date in format yyyy-mm-dd : ";
			//cin.get();
			getline(cin, date);

			string time;
			cout << "Enter time in 24 hour format(HH:mm) : ";
			getline(cin, time);

			string hall;
			cout << "Enter the hall name from following available halls" << endl;
			hallhandler->viewAvailableHalls();
			cout << endl << "Hall: ";
			getline(cin, hall);

			if (!hallhandler->reserve(hall)) {
				cout << "Enter correct Hall!!" << endl;
				cout << endl << "Hall: ";
				getline(cin, hall);
				if (hallhandler->reserve(hall)) {
					eventhandler->addEvent(name, date, time, hall,true);
				}
				else {
					cout << "Creating Event Failed" << endl;
					displayAdminMenu();
				}
			}
			else {
				eventhandler->addEvent(name, date, time, hall,true);
			}
			displayAdminMenu();

		}
		else if (choice == '2') {	// delete an event
			cin.ignore();
			cout << "Enter Event number :";
			int num = 0;
			string input="";
			cin.get();
			getline(cin, input);

			try {
				num = stoi(input);
			}
			catch (exception* e) {
				cout << "Please re-enter event number: ";
				getline(cin, input);
				cout << "input: "<<input << endl;
				if (input != "") {
					num = stoi(input);
				}
				else {
					cout << "Deleting event failed!" << endl;
					displayAdminMenu();
				}
			}
			
			cout << "Are you sure want to delete the event " << num << " (y/n)? ";

			char choice = 0;
			while (true) {
				choice = _getch();
				if (choice == 'y' || choice == 'n' || choice == 'Y' || choice == 'N') {
					break;
				}
			}
			if (choice == 'y' || choice == 'Y') {
				eventhandler->removeEvent(num);
				cout << "Event " << num << " deleted" << endl;
				displayAdminMenu();
			}
		}

		else if (choice == 'q') {
			exit(0);
		}
		else if (choice=='3') {
			cout << "Are you sure want to delete all events (y/n)? ";
			char choice = 0;
			string line;

			choice = _getch();
				cout << choice << endl;

				if (choice == 'y' || choice == 'n' || choice == 'Y' || choice == 'N') {
				}
			if (choice == 'y' || choice == 'Y') {

				if (eventhandler->deleteAllEvents()) {
					cout << "All events deleted!" << endl;
				}
				else {
					cout << "No events to delete!" << endl;
				}
			}
			else {
				cout << "events not deleted!" << endl;
			}
			displayAdminMenu();
		}
		else {	//go to back menu
			displayAdminMenu();
		}
	}
	else if (choice == '2') {	//manage halls
		hallhandler->viewHallPlan();
		displayAdminMenu();
	}
	else if (choice == '3') {
		eventhandler->getEvents();
		displayAdminMenu();
	}
	else if (choice == '4') {	//view sold tickets
		ticketshandler->printSoldTickets();
		displayAdminMenu();
	}
	else if (choice == 'q') {
		exit(0);
	}
	else {
		displayMenu(0);
	}
}

void InterfaceHandler::displayCustomerMenu()
{
	if (isloggedIn == true) {
		cout << endl <<"Customer Dashboard" << endl;
		cout <<        "==================" << endl;
		cout << "1: Buy a Ticket" << endl;
		cout << "2: View Hall Plan and reservations" << endl;
		cout << "3: Make a Hall reservation" << endl;

		cout << "q: Quit" << endl;

		char choice = getCharInput(3);

		if (choice == '2') {
			hallhandler->viewHallPlan();
			displayCustomerMenu();
		}
		else if (choice == '3') {	// make a hall reservation
			cout << "Current Events" << endl;
			cout << "==============" << endl;
			eventhandler->getEvents();

			cout << "Available Halls\n===============" << endl;
			hallhandler->viewAvailableHalls();

			cout << "Enter Event Name: ";
			string name;
			getline(cin, name);

			string date;
			cout << "Enter date in format yyyy-mm-dd : ";
			getline(cin, date);

			string time;
			cout << "Enter time in 24 hour format(HH:mm) : ";
			getline(cin, time);

			string hall;
			cout << "Enter the hall name from following available halls" << endl;
			hallhandler->viewAvailableHalls();
			cout << endl << "Hall: ";
			getline(cin, hall);

			if (!hallhandler->reserve(hall)) {
				cout << "Enter correct Hall!!" << endl;
				cout << endl << "Hall: ";
				getline(cin, hall);

					// making the payment
					cout << "Please Make the Payment of $100" << endl;
					_getch();
					cout << "Payment Done!" << endl;
					cout << endl;
				
				if (hallhandler->reserve(hall)) {
					eventhandler->addEvent(name, date, time, hall, true);
				}
				else {
					cout << "Creating Event Failed" << endl;
				}
				
			}
			else {
				// making the payment
				cout << "Please Make the Payment of $100" << endl;
				_getch();
				cout << "Payment Done!" << endl;
				cout << "Event created and Hall Reserved!" << endl;
				cout << endl;

				eventhandler->addEvent(name, date, time, hall, true);
			}
			displayCustomerMenu();
		}
		else if (choice == '1') {
			cout << endl<<"Current Events" << endl;
			cout <<       "==============" << endl;
			eventhandler->getEvents();
			ticketshandler->printAvailableTickets();

			cout << "Enter event no: ";
			string eventno;
			getline(cin, eventno);

			cout << "Enter needed ticket count: ";
			string count;
			getline(cin, count);

			// making the payment
			cout << "Please Make the Payment of $100" << endl;
			_getch();
			cout << "Payment Done!" << endl;
			cout << endl;

			ticketshandler->buyTicket(stoi(eventno)-1, stoi(count));

			displayCustomerMenu();
		}
		else if(choice=='q'){
			exit(0);
		}
		else {
			displayMenu(0);
		}
	}
}

char InterfaceHandler::getCharInput(int choices)
{
	char choice = 0;
	while (true) {
		choice = _getch();
		if (choices == 1) {
			if (choice == '1' || choice == 'q' || choice == 'b') {
				break;
			}
			else {
				cout << "please enter correct number!" << endl;
			}
		}
		else if (choices == 2) {
			if (choice == '1' || choice == '2' || choice == 'q' || choice == 'b') {
				break;
			}
			else {
				cout << "please enter correct number!" << endl;
			}
		}
		else if (choices == 3) {
			if (choice == '1' || choice == '2' || choice == '3' || choice == 'q' || choice=='b') {
				break;
			}
			else {
				cout << "please enter correct number!" << endl;
			}
		}
		else if (choices == 4) {
			if (choice == '1' || choice == '2' || choice == '3' || choice == 'q' || choice == 'b' || choice=='4') {
				break;
			}
			else {
				cout << "please enter correct number!" << endl;
			}
		}
		
	}
	return choice;
}

void InterfaceHandler::setLoggedIn()
{
	isloggedIn = true;
}