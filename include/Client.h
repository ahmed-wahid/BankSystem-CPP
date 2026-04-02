#pragma once
#include "Utils.h"
#include <string>
#include <vector>

class  Client {
private:
	std::string _AccountNumber;
	int _pinCode;
	std::string _ClientName;
	std::string _Phone;
	double _Balance;
public:

	Client(std::string _AccountNumber,int _pinCode,std::string _ClientName,std::string _Phone,double _Balance);
	Client();
	void SetAccoutNumber();
	void SetPinCode();
	void SetClientName();
	void SetPhone();
	void SetBalance();

	void SetAccoutNumber(std::string Account);
	void SetPinCode(int Pincode);
	void SetClientName(std:: string FullName);
	void SetPhone(std::string Phone);
	void SetBalance(double D);
	std::string AccoutNumber()const;
	int Pincode()const;
	std::string ClientName()const;
	std::string Phone()const;
	double  Balance()const;
	static Client ConvertStringFromVectorTOClient(std::vector<std::string> s);
	static bool SearchOnClient(std::string AcountNumber, const std::vector<Client>& clients);
	static bool SearchOnClient(std::string AcountNumber, const std::vector<Client>& clients, int& Numberofsearch);
};