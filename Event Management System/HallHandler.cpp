#include "Hallhandler.h"


HallHandler::HallHandler()
{
	hallCount = 0;
	string *data=	datahandler.fetchData(hallplan_file, &rowcount);

	int k = 0;
	vector <string> row;
	for (int i = 0; i < rowcount; i++)
	{
		for (int j = 0; j < (data+i)->length(); j++)
		{
			if (string(*(data+i))[j] == ' '){
				row.push_back((data + i)->substr(k, (j-k)));
				k = j + 1;
			}
			else if (j == (data + i)->length()-1) {
				row.push_back((data + i)->substr(k, (j - k+1 )));
			}
		}
		k = 0;
		halls.push_back(row);
		row.clear();
	}

	availableHalls = halls;
	columncount = halls.size();
	columncount++;

	hallCount = rowcount*columncount;

	int count = 0;

	data = datahandler.fetchData("reservations.txt",&count);

	for (int i = 0; i < count; i++)
	{
		if ((*(data + i)) != "") {
			reservedhalls.push_back(*(data + i));
		}
	}

	int status = checkReservations();
	if (status==1) {
		cout << "reservations.txt file contains an incorrect hall. Please check!" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		exit(1);
	}
	else if (status == 2) {	//not working
		cout << "reservations.txt has syntax errors. Please check!" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		exit(1);
	}
	
}

void HallHandler::viewHallPlan() {
	cout << endl << "Hall Plan" << endl << "---------" << endl;
	for (int i = 0; i < rowcount; i++)
	{
		for (int j = 0; j < halls[i].size(); j++)
		{
			cout << halls[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl <<"Total Hall Count : " <<hallCount << endl;
	cout << "Available halls: "<<(hallCount-reservedhalls.size()) << endl;
}

void HallHandler::printVector(vector<string> data) {
		for (int j = 0; j <data.size(); j++) {
			cout << data[j] << endl;
		}
}

void HallHandler::printVector(vector <vector<string>> data) {
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j <data[i].size(); j++) {
			cout << data[i][j]<< " ";
		}
		cout << endl;
	}
}

bool HallHandler::checkHall(string hall) {
	for (int i = 0; i < halls.size(); i++)
	{
		for (int j = 0; j <halls[i].size(); j++) {
			if (halls[i][j] == hall) {
				return true;
			}
		}
	}
	return false;
}

int HallHandler::checkReservations() {
	for (int i = 0; i < reservedhalls.size(); i++)
	{
		if (reservedhalls[i] != "") {
			if (!checkHall(reservedhalls[i])) {
				cout << reservedhalls[i] << endl;
				return 1;
			}
		}
		for (int j = 0; j < availableHalls.size(); j++)
		{
			for (int k = 0; k < availableHalls[j].size(); k++)
			{
				if (availableHalls[j][k] == reservedhalls[i]) {
					availableHalls[j][k] = " - ";
					break;
				}
			}
		}
	}
	return 0;
}

void HallHandler::viewAvailableHalls() {
	printVector(availableHalls);
	cout << "Available halls: " << (hallCount - reservedhalls.size()) << endl;
}

void HallHandler::unreserveHall(string hallno)
{
	datahandler.findanddeleteline(reservations_file, hallno);
}



bool HallHandler::reserve(string hall) {
	
	for (int j = 0; j < availableHalls.size(); j++)
	{
		for (int k = 0; k < availableHalls[j].size(); k++)
		{
			//cout << (availableHalls[j][k][0]) << endl;
			if (availableHalls[j][k] == hall ) {
				availableHalls[j][k] = "- ";
				datahandler.appendToFile(reservations_file, hall);
				datahandler.appendToFile(reservations_file, "\n");
				return true;
			}
		}
	}
	return false;
}

void HallHandler::reloadhalls()
{
	halls.clear();
	reservedhalls.clear();
	availableHalls.clear();

	hallCount = 0;
	string *data = datahandler.fetchData("hallplan.txt", &rowcount);
	//hallArray = new string*;

	int k = 0;
	vector <string> row;
	//cout << *(data + string(*data).length()) << endl;
	for (int i = 0; i < rowcount; i++)
	{
		for (int j = 0; j < (data + i)->length(); j++)
		{
			if (string(*(data + i))[j] == ' ') {
				//cout << string(*(data + i)).substr(k, 2) << endl;
				row.push_back((data + i)->substr(k, (j - k)));
				k = j + 1;
			}
			else if (j == (data + i)->length() - 1) {
				row.push_back((data + i)->substr(k, (j - k + 1)));
			}
		}
		k = 0;
		halls.push_back(row);
		row.clear();
	}

	availableHalls = halls;
	columncount = halls.size();
	columncount++;

	hallCount = rowcount*columncount;
	int count = 0;

	data = datahandler.fetchData(reservations_file, &count);

	for (int i = 0; i < count; i++)
	{
		if ((*(data + i)) != "\n") {
			reservedhalls.push_back(*(data + i));
		}
	}

	int status = checkReservations();
	if (status == 1) {
		cout << "reservations.txt file contains an incorrect hall. Please check!" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		exit(1);
	}
}