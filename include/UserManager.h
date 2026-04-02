#pragma once
#include<vector>
#include "User.h"
#include <iostream>
class UserManager {
	private:
		std::string FileUser = "data/User.txt";
	bool SearchOnUser(  std::vector <User>& Users, std::string Name, int &location );
	std::string NotRepetedUserName(std::vector <User>& Users, int& location);
	std::string EditUserNameAndNotRepetted(std::string NameOld);
	bool UserNameRepeted(std::string NewName, std::string NameOld);
public:
	
	User Login(std::vector<User>& users, int& location);
	void SearchUser(std::vector<User>& Usears, int& location);
	void DeletUser(std::vector <User>& Users, int Location, bool DoYouWantMassage = false);
	void Update(std::vector<User>& Users, int permission);
	void AddUser(std::vector<User>& Users);
	void DeletUser(std::vector <User>& Users, User MyUser);
	void AllMangeUsers(std::vector<User>& Usears, int Permissions, User user);

	void SearchUser(std::vector<User>& Usears);
};


