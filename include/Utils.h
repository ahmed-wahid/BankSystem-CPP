#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <limits>
class Utils {
	

	static bool ClearInput();
	
	
public:
	static bool ISNumber(const std::string &input);
	
	static void WaitAndReturn(std::string Message= "Press Enter to return to Main Menu...");
	static int ConvertStringToint(std::string S);
	static double ConvertStringToDouble(std::string S);
	static int AskUserForNumber(std::string Message, std::string MessageOfWrong, int start, int end);
	static double AskUserForNumberDouble(std::string Message, std::string MessageOfWrong, double start, double end);
	
	static std::string AskUserForString(std::string Message);

	static bool AskYesOrNo(std::string Message);
	static std::vector<std::string> SplitString(std::string S1, std::string Delim);
	static std::string ToLowerString(const std::string s1);
};
