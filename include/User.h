#pragma once
#include<string>
#include<iostream>
#include<vector>
class User {
private:
	std::string _UserName;
	std::string _Password;
	int _Permissions;
public:
	void SetUserName();
	std::string UserName();
	void SetPassword();
	std::string Password();

	void SetUserName(std::string UserName);
	void SetPassword(std::string Password);
	void SetPermision(int Permmision);
	void SetPermision();
	int Permission()const;
	static User ConvertStringFromVectorToUser(std::vector<std::string> s);
};