#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "../include/Client.h"
#include <fstream>
#include "../include/Utils.h"
#include "../include/User.h"

class File {

public:
	std::vector<Client> LoadDataFromFile(std::string FileName = "../data/BankSystem.txt");
	std::vector<User> LoadDataFromUsers(std::string FileName = "../data/User.txt");

	static void SaveDataTofile(std::vector<User> User, std::string fileName = "../data/User.txt");
	void SaveDataTofile(std::vector<Client> Clients, std::string fileName = "../data/BankSystem.txt");

};
