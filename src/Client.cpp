#include "../include/Client.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include "../include/Utils.h"
using namespace std;


Client::Client(std::string _AccountNumber, int _pinCode, std::string _ClientName, std::string _Phone, double _Balance) {
	this->_AccountNumber = _AccountNumber;
	this->_pinCode = _pinCode;
	this->_ClientName = _ClientName;
	this->_Phone = _Phone;
	this->_Balance = _Balance;
}
Client::Client(){}


void Client::SetAccoutNumber() {
		_AccountNumber = Utils::AskUserForString("Enter Accout Number :");

	}
void Client::SetPinCode() {
		_pinCode = Utils::AskUserForNumber("Enter pin code start with 1000 and max 1500 :", "Pin code: ", 1000, 1500);
	}
void Client::SetClientName() {
		_ClientName = Utils::AskUserForString("Enter Your Name: ");
	}
void  Client::SetPhone() {
		_Phone = Utils::AskUserForString("Enter Your Phone: ");
	}
void  Client::SetBalance() {
		_Balance = Utils::AskUserForNumberDouble("Enter your Balance minumm:0 max 1000000: ", "Balance :", 0, 1000000);
	}
void Client::SetAccoutNumber(std::string Account) {
		_AccountNumber = Account;
	}
	//oveloding
void Client::SetPinCode(int Pincode) {
		_pinCode = Pincode;
	}
void Client::SetClientName(std::string FullName) {
		_ClientName = FullName;
	}
void Client::SetPhone(std::string Phone) {
		_Phone = Phone;
	}
void Client::SetBalance(double Balance) {
		_Balance = Balance;
	}
string  Client::AccoutNumber() const {
		return _AccountNumber;
	}
int  Client::Pincode() const {
		return _pinCode;
	}
string  Client::ClientName()const {
		return _ClientName;
	}
string Client::Phone()const {
		return _Phone;
	}
double  Client::Balance() const {
		return _Balance;
	}

bool Client::SearchOnClient(string AcountNumber, const vector<Client>& clients) {

	for (int i = 0; i < clients.size(); i++) {

		if (AcountNumber == clients[i].AccoutNumber()) {
			return true;
		}


	}
	return false;

}
bool Client::SearchOnClient(string AcountNumber, const vector<Client>& clients, int& Numberofsearch) {

	for (int i = 0; i < clients.size(); i++) {

		if (AcountNumber == clients[i].AccoutNumber()) {
			Numberofsearch = i;
			return true;
		}


	}
	return false;

}
Client Client::ConvertStringFromVectorTOClient(vector<string> s) {
		Client c;
		c.SetAccoutNumber(s[0]);
		c.SetPinCode(Utils::ConvertStringToint(s[1]));

		c.SetClientName(s[2]);
		c.SetPhone(s[3]);
		c.SetBalance(Utils::ConvertStringToDouble(s[4]));
		return c;
	}
