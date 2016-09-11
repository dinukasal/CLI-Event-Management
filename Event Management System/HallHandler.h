#ifndef HALL_HANDLER
#define HALL_HANDLER

#include <iostream>
#include "DataHandler.h"
#include <vector>
#include <conio.h>

using namespace std;

class HallHandler {
private:
	int hallCount;
	DataHandler datahandler;
	int rowcount = 0, columncount = 0;
	vector <vector <string>> halls;
	vector <string> reservedhalls;
	vector <vector<string>> availableHalls;
public:
	HallHandler();	//constructor
	void viewHallPlan(); //view the hall plan
	void printVector(vector <string>); //print any vectors
	//void makeReservation();
	void printVector(vector <vector<string>>); //print vectors
	bool checkHall(string); //check if given hall name exists in the given vector
	int checkReservations(); //check reservations.txt file is valid in sytax
	bool reserve(string);
	void viewAvailableHalls();
	void unreserveHall(string hallno);
	void reloadhalls();
};

#endif // !HALL_handler
