#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <vector>

#include "Database.h"

using namespace std;
class DataHandler {
private:
	//filebuf file;
	
	string data[500];
public:
	DataHandler();
	string* fetchData(string fileName,int*);
	void appendToFile(string filename, string data);
	bool checkFile(const string& name);
	bool checkFiles(); // check for the needed text files which has data
	void clearFile(string fileName); // clear the contents of a file
	void writeFile(string filename,string data); // just writes data from the begining without newlines
	void printFile(string filename);//print all data in a file
	void findanddeleteline(string filename, string line); // find and delete a line
	void writeline(string filename, int lineno, string data); // write data to a given line
	vector <string> getLines(string filename); // get lines in a vector array without empty lines
	void printVector(vector <string>); //print any 2d vector
};

#endif // !