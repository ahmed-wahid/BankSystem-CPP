#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include "Utils.h"
#include "Client.h"
#include "User.h"

class UI {
public:
	static std::string Red();
	static std::string Green();
	static std::string Yellow();
	static std::string Cyan();
	static std::string Magenta();
	static void Sleep(int ms);
	static void Clear();
	static std::string Reset();
	static void ShowIntro();
	static void ShowMainMenu(bool ShowClient = false, bool AddClient = false, bool DeleteClient = false, bool UpdateClient = false, bool FindClient = false, bool Transactions = false, bool ManageUsers = false);
	static void PrintListClient(int num);
	static void PrintHeader();
	static void PrintClient(const Client& c);
	static void PrintClients(std::vector<Client> clients);
	static void PrintClientOption();
	static void ShowTransactionsMenu();
	static void ShowManageUsersMenu();
	static void ShowUser(User user);
	static void ShowUsersHeader(int size);
	static void ShowUsersList(std::vector<User> users);
	static void PrintInPox(std::string Message);

};


