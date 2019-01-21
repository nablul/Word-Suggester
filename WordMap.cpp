#include"WordMap.h"

//Insert word and next-word into hash table
void WordMap::inserttoMap(const std::string &word, const std::string &nextword) {
	map[word].insert(nextword);
	return;
};

//Remove misc characters from input vector and turn words all lowercase
void WordMap::processFileInput() {
	std::string tmp = "";

	for (int i = 0; i < fileInput.size(); ++i) {
		int wordLength = fileInput[i].length();
		for (int j = 0; j < wordLength; ++j) {
			//Check if misc character
			if ((isMiscChar(fileInput[i][j])) == false) {
				tmp.push_back(fileInput[i][j]);
			};
		};
		fileInput[i] = tmp;
		tmp = "";
		//Turn lowercase
		std::transform(fileInput[i].begin(), fileInput[i].end(), fileInput[i].begin(), ::tolower);
	};
};

//Helper function Check if character is misc character
bool WordMap::isMiscChar(const char &ch) {
	std::vector<char> miscCharacters = { ',','.',':',';','$','%','{','}','[',']','(',')','*','&','^','!' };
	for (int i = 0; i < miscCharacters.size(); ++i) {
		if ((ch < 65) || ((ch > 90) && (ch < 97)) || (ch >122)) {
			return true;
		};
	};
	return false;
};

//Print hash table
void WordMap::printMap() {
	for (auto itr : map) {
		std::cout << itr.first << "*" << itr.second.printList() << std::endl;
	};
};

WordMap::WordMap() {};

//Return most frequent words vector
std::vector<std::string> WordMap::nextWordSuggestions(const std::string &word) {
	if (map.find(word) != map.end()) {
		return map[word].nextWordSuggestions();
	}
	else {
		std::vector<std::string> result = {};
		return result;
	};
};

//Check if hash table contains a word
bool WordMap::contains(const std::string &word) {
	for (auto itr : map) {
		if (itr.first == word) {
			return true;
		};
	};
	return false;
};

//Return size of hash table
int WordMap::sizeMap() {
	return map.size();
};

//Save map
void WordMap::saveMap(const std::string &fileName) {
	std::ofstream outputFile;

	outputFile.open(fileName, std::ios::out, std::ofstream::trunc);

	for (auto itr : map) {
		outputFile << itr.first << "*" << itr.second.printList() << "\n";
	};

	outputFile.close();
};

//Load map
void WordMap::loadMap(const std::string &fileName) {
	std::ifstream inputFile;
	std::string line;
	std::string delimiter = "*";
	int delimiterPos;
	std::string word;
	std::string inputStr;

	inputFile.open(fileName, std::ios::in);

	//While file is not empty, retrieve line and insert into hash table
	while (std::getline(inputFile, line)) {
		delimiterPos = line.find(delimiter);
		word = line.substr(0, delimiterPos);
		inputStr = line.substr(delimiterPos + delimiter.length(), line.length() - 1);
		map[word].loadList(inputStr);
	};
};

//Load file
void WordMap::loadFile(const std::string &fileName) {
	std::string fileText = "";
	std::ifstream inFile;
	inFile.open(fileName, std::ios::in);

	//While file is not fully read, push back file content into file input vector
	if (inFile) {
		while (!inFile.eof()) {
			inFile >> fileText;
			fileInput.push_back(fileText);
		};
	};
	inFile.close();

	//Process file input vector to ensure only true words are entered into hash table
	processFileInput();
	for (int i = 0; i < fileInput.size() - 1; ++i) {
		if ((fileInput[i][0] >= 'a') && (fileInput[i][0] <= 'z')) {
			inserttoMap(fileInput[i], fileInput[i + 1]);
		};
	};
	return;
};
