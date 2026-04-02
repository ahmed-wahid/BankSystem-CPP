#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include "../include/Utils.h"
#include "../include/Client.h"
#include "../include/UI.h"
#include <thread>
#include <chrono>
#include "../include/User.h"

void UI::PrintInPox(std::string Message) {
	Reset();
	Clear();
	std::cout << "\n-----------------------------------\n";
	std::cout << "\t"<< Message;
	std::cout << "\n-----------------------------------\n";
}
std::string UI::Green() { return "\033[32m"; }
std::string UI::Yellow() { return "\033[33m"; }
std::string UI::Cyan() { return "\033[36m"; }
std::string UI::Red() { return "\033[31m"; }
std::string UI::Magenta() { return "\033[35m"; }
void UI::Sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void UI::Clear() {
	std::cout << "\033[2J\033[1;1H";
}


	std::string UI::Reset() {
		return  "\033[0m";
	}
    void UI::ShowIntro() {
		Sleep(1000);
		Clear();
		std::cout <<Reset()<< "=========================================\n";
		std::cout << "         Welcome to Bank System          \n";
		std::cout << "=========================================\n\n";
		Sleep(1000);
		
	}
	void UI::ShowMainMenu(bool ShowClient, bool AddClient, bool DeleteClient,
		bool UpdateClient, bool FindClient, bool Transactions, bool ManageUsers) {
		std::cout << "=========================================\n";
		std::cout << "            Main Menu Screen             \n";
		std::cout << "=========================================\n";
		std::cout << (!ShowClient ? Red() : Reset()) << "[1] Show Client List.\n";
		std::cout << (!AddClient ? Red() : Reset()) << "[2] Add New Client.\n";
		std::cout << (!DeleteClient ? Red() : Reset()) << "[3] Delete Client.\n";
		std::cout << (!UpdateClient ? Red() : Reset()) << "[4] Update Client Info.\n";
		std::cout << (!FindClient ? Red() : Reset()) << "[5] Find Client.\n";
		std::cout << (!Transactions ? Red() : Reset()) << "[6] Transactions.\n";
		std::cout << (!ManageUsers ? Red() : Reset()) << "[7] Mangers Users.\n";
		std::cout << Reset() << "[8] Logout.\n";
		std::cout << Reset() << "[9] Exit.\n";
		std::cout << "=========================================\n";
	}
void UI::PrintListClient (int num) {
		std::cout << "\n\t\t\tClient List ( " << num << " ) Client(s).\n";
		std::cout << "________________________________________________________________________________\n\n";
	}
void UI::PrintHeader() {

	std::cout << "| Account Number | Pin Code | Client Name            | Phone     | Balance |\n";
	std::cout << "________________________________________________________________________________\n\n";
}
void UI::PrintClient(const Client& c) {
		std::cout << "| " << std::left << std::setw(15) << c.AccoutNumber()
			<< "| " << std::setw(9) << c.Pincode()
			<< "| " << std::setw(22) << c.ClientName()
			<< "| " << std::setw(10) << c.Phone()
			<< "| " << std::setw(8) << c.Balance()
			<< "|\n";

		std::cout << "________________________________________________________________________________\n";
	}

void UI::PrintClients(std::vector<Client> clients) {

	for (int i = 0;i< clients.size(); i++) {
		UI::PrintClient(clients[i]);
	}

 }

 void UI::PrintClientOption() {
	
	std::cout <<"\n[1] " << "Client Name:\n";
		
	std:: cout << "[2] " << "Phone:\n";
		
	std::cout << "[3] " << "Balance:\n";
	


}
  void UI::ShowManageUsersMenu() {
	  Clear();

	  std::cout << "\n";
	 std::cout << "===================================================\n";
	 std::cout << "        Manage Users Menu Screen         \n";
	 std::cout << "===================================================\n";

	 std::cout << "[1] List Users.\n";
	 std::cout << "[2] Add New User.\n";
	 std::cout << "[3] Delete User.\n";
	 std::cout << "[4] Update User.\n";
	 std::cout << "[5] Find User.\n";
	 std::cout << "[6] Main Menu.\n";

	 std::cout << "====================================================\n";
 }
  void UI::ShowUsersList(std::vector<User> users ) {

	  ShowUsersHeader(users.size());
	  for (int i = 0; i < users.size(); i++) {
		  ShowUser(users[i]);
	  }

	  std::cout << "=========================================================\n";
		
  }
  void UI::ShowUsersHeader(int size) {
	  std::cout << "\nUsers List (" << size << ") User(s).\n";
	  std::cout << "====================================================\n";
	  std::cout << "" << std::left << std::setw(15) << "User Name"
		  << "| " << std::setw(15) << "Password"
		  << "| " << std::setw(12) << "Permissions" << "\n";

	  std::cout << "====================================================\n";
  }
  void UI::ShowUser(User user) {
	  std::cout << ""
		  << std::left << std::setw(15) << user.UserName()
		  << "| " << std::setw(15) << user.Password()
		  << "| " << std::setw(12) << user.Permission() << "\n";
  
  }
 void UI::ShowTransactionsMenu() {
	 std::cout << "=========================================\n";
	 std::cout << "\t   Transactions Menu Screen\n";
	 std::cout << "=========================================\n";
	 std::cout << "[1] Deposit.\n";
	 std::cout << "[2] Withdraw.\n";
	 std::cout << "[3] Total Balances.\n";
	 std::cout << "[4] Change Account Number.\n";
	 std::cout << "[5] Main Menu.\n";
	 std::cout << "=========================================\n";
 }