#include"WordList.h"

//Helper function to sort most frequent words vector 
void WordList::sortMostFequentWord() {
	bool swapped;

	//Bubble sort
	for (int i = 0; i < mostFrequentWords.size() - 1; ++i) {
		swapped = false;
		for (int j = 0; j < mostFrequentWords.size() - i - 1; ++j) {
			if (mostFrequentWords[j].second < mostFrequentWords[j + 1].second) {
				std::pair<std::string, int> tmp = mostFrequentWords[j];
				mostFrequentWords[j] = mostFrequentWords[j + 1];
				mostFrequentWords[j + 1] = tmp;
				swapped = true;
			};
		};

		//If inner loop did not run, vector already sorted, return
		if (swapped == false) {
			return;
		};
	};
};

//Default constructor: set list = null & number of top results = 0
WordList::WordList() {
	mostFrequentWords = {};
	numofresults = 5;
};

//Insertion function given a next word
void WordList::insert(const std::string &nextword) {
	std::pair<std::string, int> insertedWord;
	int insertedWordCount = 1;

	//If hash table does not contain word, insert into hash table with count = 1
	if (wordHash.find(nextword) == wordHash.end()) {
		wordHash[nextword] = 1;
		insertedWord = std::make_pair(nextword, insertedWordCount);
	}

	//If hash table contains word, increment count
	else {
		for (auto itr : wordHash) {
			if (itr.first == nextword) {
				++itr.second;
				insertedWordCount = itr.second;
			};
		};
		insertedWord = std::make_pair(nextword, insertedWordCount);
	};

	//Check if word is already part of most frequent words vector. If yes, increment count
	if (mostFrequentWords.size() == 0) {
		mostFrequentWords.push_back(insertedWord);
		return;
	}
	else {
		for (int i = 0; i < mostFrequentWords.size() - 1; ++i) {
			if (mostFrequentWords[i].first == insertedWord.first) {
				++mostFrequentWords[i].second;
				sortMostFequentWord();
				return;
			};
		};
	};

	//If word is not part of most frequent words vector, check if vector is full. If not, add to vector
	if (mostFrequentWords.size() <= numofresults) {
		mostFrequentWords.push_back(insertedWord);
		sortMostFequentWord();
		return;
	}

	//Update most frequent words vector if inserted count has higher or equal count
	for (int i = 0; i < mostFrequentWords.size() - 1; ++i) {
		if (mostFrequentWords[i].second < insertedWord.second) {
			mostFrequentWords[i] = insertedWord;
			sortMostFequentWord();
			return;
		};
	};
};

//Returns list of most frequent next words
std::vector<std::string> WordList::nextWordSuggestions() {
	std::vector<std::string> result;

	//Push most frequent word results to result vector and return
	for (int i = 0; i < mostFrequentWords.size() - 1; ++i) {
		result.push_back(mostFrequentWords[i].first);
	};
	return result;
};

//Prints hash table and most frequent words to a string output
std::string WordList::printList() {
	std::string result;

	for (auto itr : wordHash) {
		result = result + itr.first + "," + std::to_string(itr.second) + "|";
	};
	result = result + "-";
	for (auto itr : mostFrequentWords) {
		result = result + itr.first + "," + std::to_string(itr.second) + "|";
	};
	return result;
};

//Turns string input to hash table and most frequent words
void WordList::loadList(const std::string &inputStr) {
	std::string delimiter = "-";
	std::string listDelimiter = "|";
	std::string pairDelimiter = ",";
	std::string listStr;
	std::string mostFrequentWordsStr;
	std::string token;
	std::string word;
	int frequency;
	int pairDelimiterPos;

	//Find location of split between word list and most frequently used words list 
	int delimiterPos = inputStr.find(delimiter);
	listStr = inputStr.substr(0, delimiterPos);
	mostFrequentWordsStr = inputStr.substr(delimiterPos + delimiter.length(), inputStr.length() - 1);

	//Parse word list and populate hash table
	delimiterPos = 0;
	while ((delimiterPos = listStr.find(listDelimiter)) != std::string::npos) {
		token = listStr.substr(0, delimiterPos);
		pairDelimiterPos = token.find(pairDelimiter);
		word = token.substr(0, pairDelimiterPos);
		frequency = std::stoi(token.substr(pairDelimiterPos + pairDelimiter.length(), token.length() - 1));
		wordHash[word] = frequency;
		listStr.erase(0, delimiterPos + listDelimiter.length());
	};

	//Parse most frequently used words list and populate vector
	delimiterPos = 0;
	while ((delimiterPos = mostFrequentWordsStr.find(listDelimiter)) != std::string::npos) {
		token = mostFrequentWordsStr.substr(0, delimiterPos);
		pairDelimiterPos = token.find(pairDelimiter);
		word = token.substr(0, pairDelimiterPos);
		frequency = std::stoi(token.substr(pairDelimiterPos + pairDelimiter.length(), token.length() - 1));
		mostFrequentWords.push_back(std::make_pair(word, frequency));
		mostFrequentWordsStr.erase(0, delimiterPos + listDelimiter.length());
	};
};