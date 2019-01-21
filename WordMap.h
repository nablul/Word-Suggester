#ifndef WORDSUGGESTER_WORDMAP_H_
#define WORDSUGGESTER_WORDMAP_H_

#include<algorithm>
#include<iostream>
#include<fstream>
#include"WordList.h"

class WordMap {
private:
	std::unordered_map<std::string, WordList> map;

	//Insert word and next-word into hash table
	void inserttoMap(const std::string &word, const std::string &nextword);

	//Remove misc characters from input vector and turn words all lowercase
	void processFileInput();

	//Helper function Check if character is misc character
	bool isMiscChar(const char &ch);

	//Print hash table
	void printMap();

public:
	WordMap() {};
	std::vector<std::string> fileInput;

	//Return most frequent words vector
	std::vector<std::string> nextWordSuggestions(const std::string &word);

	//Check if hash table contains a word
	bool contains(const std::string &word);

	//Return size of hash table
	int sizeMap();

	//Save map
	void saveMap(const std::string &fileName);

	//Load map
	void loadMap(const std::string &fileName);

	//Load file
	void loadFile(const std::string &fileName);
};

#endif