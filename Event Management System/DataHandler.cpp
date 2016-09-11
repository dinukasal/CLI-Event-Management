#include "DataHandler.h"

using namespace std;

DataHandler::DataHandler() {

}


string* DataHandler::fetchData(string fileName,int *count){
	ifstream fileInput(fileName);
	if (fileInput.is_open()) {
		string line;
		int counter=0;
		while (getline(fileInput, line)) {
			//cout << line << '\n';
			//if ((unsigned int)line[0] == 0 || (line[0] == '/' && line[1] == '/') ) {
			if ((line[0] == '/' && line[1] == '/')) {
			}
			else {
				data[counter++] = line;
			}
		}
		//cout << "inserted " << data.size() << " lines to data" << endl;
		fileInput.close();
		*count = counter;
		
		return data;
	}
	else {
		cout << "cannot open the file" << fileName << endl;
	}
}

void DataHandler::appendToFile(string filename, string data) {
	ofstream outfile;
	outfile.open(filename, ios_base::app | ios::out);
	outfile << data;
	outfile.close();
}

bool DataHandler::checkFile(const string& name)
{
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
}

bool DataHandler::checkFiles()
{
	if (!checkFile(admin_file)) {
		cout << "Admin Login File is missing!" << endl;
	}
	else {
		if (!checkFile(customers_file)) {
			cout << "Customers login File is missing!" << endl;
		}
		else {
			if (!checkFile(events_file)) {
				cout << "Events file is missing!" << endl;
			}
			else {
				if (!checkFile(hallplan_file)) {
					cout << "Hall Plan file is missing!" << endl;
				}
				else {
					if (!checkFile(reservations_file)) {
						cout << "Reservations file is missing!" << endl;
					}
					else {
						if (!checkFile(ticket_file)) {
							cout << "Tickets file is missing!" << endl;
						}
						else {
							return true;
						}
					}
				}
			}
		}

	}
	return false;
}

void DataHandler::clearFile(string fileName)
{
	int linecount=0;
	string* data = fetchData(fileName, &linecount);

	for (int i = 0; i < linecount; i++) {
		writeFile(fileName,"");
	}

}

void DataHandler::writeFile(string filename,string data)
{
	ofstream file(filename, ios::out);
	if (file.is_open()) {
		file << data ;
	}
	else {
		cout << "Error opening file "<<filename;
	}
	file.close();
}

void DataHandler::printFile(string filename)
{
	int linecount = 0;
	string* line = fetchData(filename, &linecount);

	for (int i = 0; i < linecount; i++) {
		cout << (*line) << endl;
	}
}

void DataHandler::findanddeleteline(string filename, string line)
{
	vector <string> temp;
	ifstream file;

	file.open(filename, ios::in);

	string oneline;

	while (getline(file, oneline)) {
		temp.push_back(oneline);
	}

	for (int i = 0; i <temp.size() ; i++)
	{
		if (temp[i] == line) {
			writeline(filename, i, "");
		}
	}
}

void DataHandler::writeline(string filename, int lineno, string data)
{ // function is working
	fstream file;
	file.open(filename, ios::in);
	string line;
	vector <string> buffer;

	int counter = 0;

	if (file.is_open()) {
		while (getline(file, line)) {
			buffer.push_back(line);
			if (line != "") {
				
				//cout << line << endl;
			}	
		}

		//cout << data << endl;

		file.close();	//closing the opened file for reading ****

		ofstream file;
		file.open(filename, ios::out );	//opening file in out mode clears the file
		file.close();

		file.open(filename, ios::out| ios::app);
		//file.write(line.c_str(),line.length());
		
		if (buffer.size()-1 >= lineno) {
			buffer[lineno] = data;

		}else {
			for (int i = buffer.size()-1; i < lineno; i++) {
				if (i == (lineno-1)) {
					buffer.push_back(data);
				}
				else {
					buffer.push_back("");
				}
				
			}
		}
		for (int i = 0; i < buffer.size(); i++) {
			file << buffer[i] << endl;
		}

		//file <<data << endl;
		file.close();
	}
	else {
		cout << "error opening file " << filename << endl;
	}
}

vector<string> DataHandler::getLines(string filename)
{
	vector <string> data;
	int count = 0;
	string* lines = fetchData(filename, &count);

	for (int i = 0; i < count; i++) {
		if (*(lines + i) != "") {
			data.push_back(*(lines + i));
		}
	}
	return data;
}

void DataHandler::printVector(vector<string> data) {
	for (int j = 0; j <data.size(); j++) {
		cout << data[j] << endl;
	}
}