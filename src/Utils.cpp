#include "../include/Utils.h"
#include "../include/UI.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
using namespace std;

// Check if the given string represents a valid number (int or double)
bool Utils::ISNumber(const string& input) {
	if (input.empty())
		return false;

	try {
		size_t pos;
		stod(input, &pos); // Try converting to double

		// Ensure full string is numeric (no extra characters)
		return pos == input.length();
	}
	catch (...) {
		return false; // Conversion failed
	}
}

// Convert string to integer safely (returns 0 if invalid)
int Utils::ConvertStringToint(string S) {
	if (ISNumber(S)) {
		return stoi(S);
	}
	return 0;
}

// Convert string to double safely (returns 0.0 if invalid)
double Utils::ConvertStringToDouble(string S) {
	if (ISNumber(S)) {
		return stod(S);
	}
	return 0.0;
}

// Convert all characters in string to lowercase
string Utils::ToLowerString(string s1) {
	for (int i = 0; i < s1.length(); i++) {
		s1[i] = (char)tolower(s1[i]);
	}
	return s1;
}

// Clear input buffer if cin fails (invalid input handling)
bool Utils::ClearInput() {
	if (cin.fail()) {
		cin.clear(); // reset error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
		return true;
	}
	return false;
}

// Ask user for integer within a specific range
int Utils::AskUserForNumber(string Message, string MessageOfWrong, int start, int end) {
	int num = 0;

	cout << Message << endl;

	while (true) {
		cin >> num;

		// Handle invalid input OR out-of-range values
		if (Utils::ClearInput() || !(num <= end && num >= start)) {
			cout << "\n" << UI::Red() << MessageOfWrong << UI::Reset();
			continue;
		}

		return num;
	}
}

// Ask user for double within a specific range
double Utils::AskUserForNumberDouble(string Message, string MessageOfWrong, double start, double end) {
	double num = 0;

	cout << Message << endl;

	while (true) {
		cin >> num;

	
		
		if (num <= end && num >= start)
			return num;
		else {

			Utils::ClearInput();
			cout << "\n" << UI::Red() << MessageOfWrong << UI::Reset();
			continue;
		}
	}
}

// Ask user for a non-empty string input
string Utils::AskUserForString(string Message) {
	string input;

	while (true) {
		cout << Message;
		
			// Read full line (handles spaces correctly)
			getline(cin >> ws, input);
		if (!input.empty())
			return input;

		cout << "Input cannot be empty, try again.\n";
	}
}

// Ask user for Yes/No input and return boolean
bool Utils::AskYesOrNo(string message) {
	string answer;

	while (true) {
		cout << message << endl;;
		cin >> answer;

		answer = ToLowerString(answer);

		if (answer == "y" || answer == "yes" || answer == "1" || answer == "true" || answer == "t" ||answer=="ok")
			return true;

		if (answer == "n" || answer == "no" || answer == "0" || answer == "false" || answer == "f")
			return false;

		cout << UI::Red()<< "Invalid input. Please enter yes or no."<< UI::Reset() << endl;
	}
}

// Split string using a delimiter and return vector of substrings
vector<string> Utils::SplitString(string S1, string Delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = S1.find(Delim)) != string::npos) {
		sWord = S1.substr(0, pos);

		if (sWord != "") {
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());
	}

	// Add remaining part
	if (S1 != "") {
		vString.push_back(S1);
	}

	return vString;
}

// Pause execution until user presses 


void Utils::WaitAndReturn(std::string Message ) {
	std::cout << "\n" << Message;

	// تنظيف أي بقايا في المدخلات السابقة

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cin.get(); // انتظار الض
}