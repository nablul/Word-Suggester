#ifndef WORDSUGGESTER_WORDSUGGESTER_DRIVER_H_
#define WORDSUGGESTER_WORDSUGGESTER_DRIVER_H_

#include"dirent.h"
#include"WordMap.h"

class WordSuggester_Driver {
private:
	WordMap map;
	std::string command;

	//Function to load all files in a directory. ONLY USED TO INITIALIZE WORD LIBRARY
	void loadDirectory(const std::string &directoryPath);

public:
	//Default constructor
	WordSuggester_Driver();

	//UI function
	void run();
};

#endif