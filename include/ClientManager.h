#pragma once
#include <vector>
#include "Utils.h"
#include "Client.h"
class ClientManager {
private:
	std::vector<Client> clients;

	std::string NotRepetedAccountNumber(const std::vector<Client>& clients);
	
public:
	int FindClientIndex(const std::vector<Client>& clients);
	void AddClient(std::vector<Client>& clients);
	void DeleteClient(std::vector<Client>& clients);
	void SearchClient(const std::vector<Client>& clients);
	void UpdateClient(std::vector<Client>& clients);
	void Transcations(std::vector<Client>& clients);

};