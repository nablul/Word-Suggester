#ifndef WORDSUGGESTER_WORDLIST_H_
#define WORDSUGGESTER_WORDLIST_H_

#include"unordered_map"
#include"string"

class WordList {
private:
	//Hash table of next words
	std::unordered_map<std::string, int> wordHash;

	//Vector stores list of most frequent next words
	std::vector<std::pair<std::string, int>> mostFrequentWords;
	int numofresults;

	//Helper function to sort most frequent words vector 
	void sortMostFequentWord();

public:
	//Default constructor: set list = null & number of top results = 0
	WordList();

	//Insertion function given a next word
	void insert(const std::string &nextword);

	//Returns list of most frequent next words
	std::vector<std::string> nextWordSuggestions();

	//Prints hash table and most frequent words to a string output
	std::string printList();

	//Turns string input to hash table and most frequent words
	void loadList(const std::string &inputStr);
};

#endif