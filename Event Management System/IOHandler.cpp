#include "IOHandler.h"

IOHandler::IOHandler(UserHandler* outerUsers,EventHandler* eventhandler,HallHandler* hallhandler, TicketsHandler* tickets) {
	users= outerUsers;
	IOHandler::eventhandler = eventhandler;
	IOHandler::hallhandler = hallhandler;
	isloggedIn = false;
	IOHandler::ticketshandler = tickets;
}

void IOHandler::displayMenu(int number)
{
	char choice = 0;
	switch (number) {
	case 0:
		cout << "Event System" << endl;
		cout << "============" << endl << endl;
		cout << "1- View Events" << endl;
		cout << "2- Login Administrator" << endl;
		cout << "3- Login Customer" << endl;
		cout << "q- exit" << endl;
		cout << "b- go back" << endl;
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

void IOHandler::getInput()
{
	char choice = 0;
	while (true) {
		choice = _getch();	
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
	else if (choice == '1') { 
		eventhandler->getEvents();
		displayMenu(0);
	}
	else if (choice == 113) {
		exit(0);
	}

}

void IOHandler::login(char choice)
{
	string username;
	string password;

	if (isdigit(choice)) {

		switch (choice) {
		case '2':
			cout << "Administrator login" << endl;
			cout << "===================" << endl;
			cout << "Username-";
			cin >> username;
			cout << "Passsword-";
			cin >> password;


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
			cout << "Username-";
			getline(cin, username);
			cout << "Password-";

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

void IOHandler::displayAdminMenu()
{
	cout << endl <<"Administrator Dashboard" << endl;
	cout << "==============" << endl;

	cout << "1- Manage Events " << endl;
	cout << "2- Manage Halls" << endl;
	cout << "3- View Events" << endl;
	cout << "4- View Sold Tickets" << endl;

	cout << "q- Quit" << endl;

	char choice = getCharInput(4);

	if (choice == '1') {
		eventhandler->getEvents();
		ticketshandler->printSoldTickets();

		cout << endl;
		cout << "1- Create an event" << endl;
		cout << "2- Delete an event" << endl;
		cout << "3- Delete All events" << endl;

		char choice = getCharInput(3);

		if (choice == '1') {
			cout << "Enter Event Name- ";
			string name;
			getline(cin, name);

			string date;
			cout << "Enter date - ";
			getline(cin, date);

			string time;
			cout << "Enter time (HH:mm) - ";
			getline(cin, time);

			string hall;
			cout << "Enter the hall name " << endl;
			hallhandler->viewAvailableHalls();
			cout << endl << "Hall- ";
			getline(cin, hall);

			if (!hallhandler->reserve(hall)) {
				cout << "Enter correct Hall!!" << endl;
				cout << endl << "Hall- ";
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
			cout << "Enter Event number -";
			int num = 0;
			string input="";
			cin.get();
			getline(cin, input);

			try {
				num = stoi(input);
			}
			catch (exception* e) {
				cout << "Please re-enter event number- ";
				getline(cin, input);
				cout << "input- "<<input << endl;
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

void IOHandler::displayCustomerMenu()
{
	if (isloggedIn == true) {
		cout << endl <<"Customer Dashboard" << endl;
		cout <<        "==================" << endl;
		cout << "1- Buy a Ticket" << endl;
		cout << "2- Cancel a Ticket" << endl;
		cout << "3- View Hall Plan and reservations" << endl;
		cout << "4- Reserve a hall" << endl;
		cout << "5- Cancel a hall reservation" << endl;

		cout << "q- Quit" << endl;

		char inputkey = getCharInput(4);
		
		if (inputkey == '2') {	//cancelling a ticket
			cout << "Enter the event number: ";
			int event_no=0;
			cin >> event_no;
			cout << "Enter the ticket count to cancel: ";
			int count = 0;
			cin >> count;

			ticketshandler->cancelTicket(event_no,count);

			cout << "Ticket successfully cancelled" << endl;
			displayCustomerMenu();
		}
		else if (inputkey == '3') {
			hallhandler->viewHallPlan();
			displayCustomerMenu();
		}
		else if (inputkey == '4') {	// make a hall reservation
			cout << "Current Events" << endl;
			cout << "==============" << endl;
			eventhandler->getEvents();

			cout << "Available Halls\n===============" << endl;
			hallhandler->viewAvailableHalls();

			cout << "Enter Event Name- ";
			string name;
			getline(cin, name);

			string date;
			cout << "Enter date - ";
			getline(cin, date);

			string time;
			cout << "Enter time (HH-mm) - ";
			getline(cin, time);

			string hall;
			cout << "Enter the hall name" << endl;
			hallhandler->viewAvailableHalls();
			cout << endl << "Hall- ";
			getline(cin, hall);

			if (!hallhandler->reserve(hall)) {
				cout << "Enter correct Hall!!" << endl;
				cout << endl << "Hall- ";
				getline(cin, hall);

					// making the payment
					cout << "Make a Payment of $250" << endl;
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
				cout << "Make a Payment of $250" << endl;
				_getch();
				cout << "Payment Done!" << endl;
				cout << "Event created and Hall Reserved!" << endl;
				cout << endl;

				eventhandler->addEvent(name, date, time, hall, true);
			}
			displayCustomerMenu();
		}
		else if (inputkey == '1') {
			cout << endl<<"Current Events" << endl;
			cout <<       "==============" << endl;
			eventhandler->getEvents();
			ticketshandler->printAvailableTickets();

			cout << "Enter event no- ";
			string eventno;
			getline(cin, eventno);

			cout << "Enter needed ticket count- ";
			string count;
			getline(cin, count);

			// making the payment
			cout << "Make a Payment of $250" << endl;
			_getch();
			cout << "Payment Done!" << endl;
			cout << endl;

			ticketshandler->buyTicket(stoi(eventno)-1, stoi(count));

			displayCustomerMenu();
		}
		else if(inputkey=='q'){
			exit(0);
		}
		else {
			displayMenu(0);
		}
	}
}

char IOHandler::getCharInput(int choices)
{
	char inputkey = 0;
	while (true) {
		inputkey = _getch();
		if (choices == 1) {
			if (inputkey == '1' || inputkey == 'q' || inputkey == 'b') {
				break;
			}
			else {
				cout << "Enter correct number!" << endl;
			}
		}
		else if (choices == 2) {
			if (inputkey == '1' || inputkey == '2' || inputkey == 'q' || inputkey == 'b') {
				break;
			}
			else {
				cout << "Enter correct number!" << endl;
			}
		}
		else if (choices == 3) {
			if (inputkey == '1' || inputkey == '2' || inputkey == '3' || inputkey == 'q' || inputkey=='b') {
				break;
			}
			else {
				cout << "Enter correct number!" << endl;
			}
		}
		else if (choices == 4) {
			if (inputkey == '1' || inputkey == '2' || inputkey == '3' || inputkey == 'q' || inputkey == 'b' || inputkey=='4') {
				break;
			}
			else {
				cout << "Enter correct number!" << endl;
			}
		}
		else if (choices == 5) {
			if (inputkey == '1' || inputkey == '2' || inputkey == '3' || inputkey == '4' || inputkey == '5' || inputkey == 'q' || inputkey == 'b') {
				break;
			}
			else {
				cout << "Enter correct number!" << endl;
			}
		}
		
	}
	return inputkey;
}

void IOHandler::setLoggedIn()
{
	isloggedIn = true;
}