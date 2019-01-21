#include"WordSuggester_Driver.h"

//Function to load all files in a directory. ONLY USED TO INITIALIZE WORD LIBRARY
void WordSuggester_Driver::loadDirectory(const std::string &directoryPath) {

	DIR *dir;
	struct dirent *ent;
	const char* dirPath = directoryPath.c_str();
	if ((dir = opendir(dirPath)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			std::string fileName = ent->d_name;

			//Check if file name is valid
			if (((fileName[0] >= 48) && (fileName[0] <= 57)) || ((fileName[0] >= 65) && (fileName[0] <= 90)) || ((fileName[0] >= 97) && (fileName[0] <= 122))) {
				map.loadFile(fileName);
				map.saveMap("wordMap.txt");
				std::cout << "file: " << fileName << " loaded.\n";
			};
		}
		closedir(dir);
	}
	else {
		return;
	};
};

//Default constructor
WordSuggester_Driver::WordSuggester_Driver() {
	//loadDirectory("C:\\Users\\nablul.haseeb\\source\\repos\\wordPredictor\\wordPredictor\\Books");
	map.loadMap("wordMap.txt");
	run();
};

//UI function
void WordSuggester_Driver::run() {
	std::cout << "Welcome to the Word Predictor application! This application provides next word suggestions based on\n";
	std::cout << "data from approximately hundred books. Please use the following commands to navigate the application: \n\n";
	std::cout << "Load: Load existing word suggestions saved under wordMap.txt\n";
	std::cout << "LoadFile: Load additional .txt file into to increase word suggestions\n";
	std::cout << "Size: Displays number of words currently stored in library\n";
	std::cout << "Save: Save word suggestions under wordMap.txt\n";
	std::cout << "Run: Run application and get word suggestions.\n";
	std::cout << "ExitApp: Exit application\n";

	while (true) {
		std::cout << "\n";
		std::cout << ">> ";
		std::cin >> command;
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);

		if (command == "load") {
			map.loadMap("wordMap.txt");
			std::cout << "\n";
		}
		else if (command == "loadfile") {
			std::cout << "\n";
			std::cout << "Enter file to be loaded: ";
			std::string fileName;
			std::cin >> fileName;
			map.loadFile(fileName);
			std::cout << "\n";
			std::cout << "File loaded successfully!";
			std::cout << "\n";
		}
		else if (command == "size") {
			std::cout << "Current number of words in library: " << map.sizeMap();
			std::cout << "\n";
		}
		else if (command == "save") {
			map.saveMap("wordMap.txt");
			std::cout << "File saved successfully!";
			std::cout << "\n";
		}
		else if (command == "run") {
			std::string word;
			std::vector<std::string> nextWords;

			std::cout << "Enter word:\n";
			while (word != "exitapp") {
				std::cin >> word;
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);

				if (!map.contains(word)) {
					std::cout << "Word not part of loaded library, sorry\n";
				}
				else {
					std::cout << "Next word suggestions: {";
					nextWords = map.nextWordSuggestions(word);
					for (int i = 0; i < nextWords.size(); ++i) {
						if (i == 0) {
							std::cout << nextWords[i];
						}
						else {
							std::cout << ", " << nextWords[i];
						};
					};
					std::cout << "}";
					std::cout << "\n";
				};
				std::cout << "\n";
			};
			return;
		}
		else if (command == "exitapp") {
			return;
		}
		else {
			std::cout << "Invalid command. Please enter a valid command\n";
		};
	};
};
