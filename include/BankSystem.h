#pragma once
#include "User.h"
#include "UserManager.h"
#include "Utils.h"
#include "FileManager.h"
#include "ClientManager.h"
#include "UI.h"
#include "States.h"
#include <vector>
class BankSystem {
private:
	std::string FileUser = "data/User.txt";
	std::string FileClient = "data/BankSystem.txt";
	ClientManager MangerClient;
	std::vector<Client> Vclients;
	File fileBank;
	UserManager MangerUser;
	std::vector<User>VUsers;
	User user;
	bool again = true;
	int LocationInVector;

	bool HasPermission(const User& user, Permission perm);
public:
	BankSystem();
	void Start();
};