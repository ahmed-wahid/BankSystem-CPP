#include "../include/FileManager.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "../include/Client.h"
#include "../include/User.h"
using namespace std;

// Load all clients from file into vector<Client>
vector<Client> File::LoadDataFromFile(string FileName) {

	vector<Client> Clients;
	Client client;
	string line = "";
	vector<string> VString;

	ifstream file(FileName);

	// Check if file exists / opened correctly
	if (!file) {
		cout << "File not include";
		return Clients;
	}

	// Read file line by line
	while (getline(file, line)) {

		// Split line into fields using delimiter ##
		VString = Utils::SplitString(line, "##");

		// Convert string vector to Client object
		client = Client::ConvertStringFromVectorTOClient(VString);

		// Add to list
		Clients.push_back(client);
	}

	file.close();

	return Clients;
}

// Load all users from file into vector<User>
vector<User> File::LoadDataFromUsers(std::string FileName) {

	vector<User> Users;
	string line = "";
	User user;

	ifstream File(FileName);

	// Check if file exists
	if (!File) {
		cout << "File not include";
		return Users;
	}

	// Read each line and convert to User object
	while (getline(File, line)) {

		user = user.ConvertStringFromVectorToUser(
			Utils::SplitString(line, "###")
		);

		Users.push_back(user);
	}

	return Users;
}

// Save all clients to file (overwrite mode)
void File::SaveDataTofile(vector<Client> Clients, string fileName) {

	ofstream file(fileName);

	// Write each client in formatted line
	for (int i = 0; i < Clients.size(); i++) {

		file << Clients[i].AccoutNumber() << "##"
			<< Clients[i].Pincode() << "##"
			<< Clients[i].ClientName() << "##"
			<< Clients[i].Phone() << "##"
			<< Clients[i].Balance() << "\n";
	}

	file.close();
}

// Save all users to file (overwrite mode)
void File::SaveDataTofile(vector<User> User, string fileName) {

	ofstream file(fileName);

	// Write each user in formatted line
	for (int i = 0; i < User.size(); i++) {

		file << User[i].UserName() << "###"
			<< User[i].Password() << "###"
			<< User[i].Permission() << "\n";
	}

	file.close();
}