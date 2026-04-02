#include "../include/ClientManager.h"
#include <vector>
#include "../include/Utils.h"
#include "../include/UI.h"
#include "../include/States.h"
#include <iostream>
using namespace std;

// Find client index by account number (keeps asking until found)
int ClientManager::FindClientIndex(const vector<Client>& clients) {

	int num;
	if (clients.empty()) {
		return -1;
	}
	for (int count =1;count <5 ;count++){
		string a = Utils::AskUserForString("Enter Account number to search: ");

		// boolean Search client by account number 
		if (Client::SearchOnClient(a, clients, num)) {
			break;
		}
		else {
			cout << UI::Red()  << "Erorr Acount Number not Found "  << "Attemps faild ( " << count <<"/4 )" << " : " << UI::Reset() << endl;
			if (count == 0) { return -1;}
			continue;
		}
	}

	return num;
}

// Ensure account number is unique before adding new client
string ClientManager::NotRepetedAccountNumber(const vector<Client>& clients) {

	string a = Utils::AskUserForString("Enter Account Number : ");

	while (true) {

		// Check if account number already exists
		if (!Client::SearchOnClient(a, clients)) {
			return a;
		}
		else {
			a = Utils::AskUserForString(
				UI::Red() + "Account number \"" + a + "\" already exists. Please enter another: "
				+ UI::Reset()
			);
		}
	}

	return "";
}

// Add new client with confirmation before saving
void ClientManager::AddClient(vector<Client>& clients) {

	Client client;
	bool Sure = true;

	while (Sure) {

		// Collect client data
		client.SetAccoutNumber(NotRepetedAccountNumber(clients));
		client.SetPinCode();
		client.SetClientName();
		client.SetPhone();
		client.SetBalance();

		// Show client preview
		UI::PrintHeader();
		UI::PrintClient(client);

		// Confirm before adding
		if (Utils::AskYesOrNo("Are You Sure to Add ?y/n ")) {
			Sure = false;
		}
	}

	// Add client to vector
	clients.push_back(client);

	cout << UI::Green() << "Add successfully ......" << UI::Reset();
}

// Delete client by account number
void ClientManager::DeleteClient(vector<Client>& clients) {

	int num;

	while (true) {

		string a = Utils::AskUserForString("Enter Your Acount Number to delete: ");

		if (Client::SearchOnClient(a, clients, num)) {
			UI::PrintHeader();
			UI::PrintClient(clients[num]);
			if (Utils::AskYesOrNo("Are You Sure To delete/y/n")) {
				clients.erase(clients.begin() + num);

				cout << UI::Cyan() << "Delete successfully ......" << UI::Reset();

				break;
			}
		}
		else {
			cout << UI::Red() << "Erorr Acount Number not include :" << UI::Reset() << endl;
			continue;
		}
	}
}

// Search and display a client
void ClientManager::SearchClient(const vector<Client>& clients) {

	int num = FindClientIndex(clients);

	UI::PrintHeader();
	UI::PrintClient(clients[num]);
}

// Update client data (name / phone / balance.....)
void ClientManager::UpdateClient(vector<Client>& clients) {

	int LocationClientInVector;
	int numberOfChice = 0;
	int attempts = 0;
	string a;

	while (attempts < 4) {

		a = Utils::AskUserForString("Enter account number to update: ");

		if (Client::SearchOnClient(a, clients, LocationClientInVector)) {
			break;
		}

		attempts++;

		cout << UI::Red()
			<< "Account number \"" << a << "\" not found. "
			<< "Attempt (" << attempts << "/4)"
			<< UI::Reset() << endl;

		if (attempts == 4) {
			if (!Utils::AskYesOrNo("Do you want to try again? (y/n): ")) {
				return;
			}
			attempts = 0; // reset attempts
		}
	}

	// Update loop
	while (true) {

		UI::PrintClientOption();

		numberOfChice = Utils::AskUserForNumber("What choice: ", "Choice(1-3): ", 1, 3);

		if (numberOfChice == 1) {
			clients[LocationClientInVector].SetClientName();
		}
		else if (numberOfChice == 2) {
			clients[LocationClientInVector].SetPhone();
		}
		else {
			clients[LocationClientInVector].SetBalance();
		}
		UI::PrintHeader();
		UI::PrintClient(clients[LocationClientInVector]);

		// Ask if user wants more edits
		if (!Utils::AskYesOrNo("Do you want anything else? (y/n):\n ")) {
			break;
		}	
	
	}
}

// Handle all transactions (Deposit / Withdraw / Total Balance)
void ClientManager::Transcations(vector<Client>& clients ) {

	double TotalBalances = 0;
	int index = FindClientIndex(clients);
	while (true) {
		
		UI::ShowTransactionsMenu();
	
		if (index == -1) {
			cout << "Client not found\n";
			break;
		}
		

		int Transaction = Utils::AskUserForNumber("What choice 1 to 4: ", "Enter (1 to 5)", 1, 5);

		TransactionsMenuOption TMO = static_cast<TransactionsMenuOption>(Transaction);
		
		switch (TMO) {
		
		case TransactionsMenuOption::Deposit: {
			
			UI::PrintInPox("Deposit Screen");
			UI::PrintHeader();
			UI::PrintClient(clients[index]);

			while (true) {

				double numberDepiste = Utils::AskUserForNumberDouble("Enter what do you want Deposit ?","Deposit minimum 1: ",1, 1000000);
				string message = "Are you sure to add :" + to_string(numberDepiste )+ " ? y / n \n";
				if (Utils::AskYesOrNo(message)) {

					// Add balance
					clients[index].SetBalance(clients[index].Balance() + numberDepiste);
					cout << UI::Green()
						<< "Balance updated to " << clients[index].Balance()
						<< UI::Reset() << endl;
					break;
				}
			}

			break;
		}

		case TransactionsMenuOption::Withdraw: {

			UI::PrintInPox("Withdraw Screen");

			UI::PrintHeader();
			UI::PrintClient(clients[index]);

			while (true) {

				string SBalance = to_string(clients[index].Balance()-1);

				double numWithDraw = Utils::AskUserForNumberDouble("Enter what do you want Withdraw ?","It is not possible to deduct \" " + SBalance + " \" : ",
					1,(clients[index].Balance()-1));
				if ((clients[index].Balance() - numWithDraw) <= 1) {
					break;
				}
				string message = "Are you sure to Withdraw :" + to_string(numWithDraw) + " ? y / n \n";
				if (Utils::AskYesOrNo(message)) {

					// Deduct balance
					clients[index].SetBalance(clients[index].Balance() - numWithDraw);
					cout << UI::Green()
						<< "Balance updated to " << clients[index].Balance()
						<< UI::Reset() << endl;
					break;
				}
			}

			break;
		}

		case TransactionsMenuOption::TotalBalances:

			TotalBalances = 0;

			UI::PrintClients(clients);

			for (int i = 0; i < clients.size(); i++) {
				TotalBalances += clients[i].Balance();
			}

			cout << "\t\t\t\tTotalBalance= " << TotalBalances<<endl;

			break;
		case TransactionsMenuOption::ChangeAccountNumber:
			UI::PrintInPox("Change Account Number");
		
			index = FindClientIndex(clients);
			
			break;

		default:
			return;
		}
	}
}