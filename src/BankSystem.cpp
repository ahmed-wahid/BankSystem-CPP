#include "../include/BankSystem.h"
#include "../include/ClientManager.h"
#include "../include/FileManager.h"
#include "../include/Utils.h"
#include "../include/Client.h"
#include "../include/UI.h"
#include "../include/States.h"
#include "../include/User.h"
#include "../include/UserManager.h"

using namespace std;

// Check if user has specific permission using bitmask
bool BankSystem::HasPermission(const User& user, Permission perm)
{
	return (user.Permission() & (int)perm) == (int)perm;
}

// Constructor: load data and perform login
BankSystem::BankSystem() {

	// Load clients and users from files
	Vclients = fileBank.LoadDataFromFile(FileClient);
	VUsers = fileBank.LoadDataFromUsers(FileUser);

	// Perform login and store current user
	user = MangerUser.Login(VUsers, LocationInVector);
}

// Main system loop
void BankSystem::Start() {

	while (again) {

		//string FileUserName = "BankSystem.txt";

		// Show UI
		UI::ShowIntro();

		// Show menu based on user permissions
		UI::ShowMainMenu(
			HasPermission(user, Permission::ShowClients),
			HasPermission(user, Permission::AddClient),
			HasPermission(user, Permission::DeleteClient),
			HasPermission(user, Permission::UpdateClient),
			HasPermission(user, Permission::FindClient),
			HasPermission(user, Permission::Transcations),
			HasPermission(user, Permission::ManageUsers)
		);

		// Get user choice
		int num = Utils::AskUserForNumber("What choice 1 to 8:  ", "Error chice from 1 to 9: ", 1, 9);

		MainMenuOption Choice = static_cast<MainMenuOption>(num);

		switch (Choice) {

		case MainMenuOption::ShowClients:

			if (HasPermission(user, Permission::ShowClients)) {

				UI::PrintListClient(Vclients.size());
				UI::PrintHeader();
				UI::PrintClients(Vclients);

				Utils::WaitAndReturn();
			}
			else {
				cout << UI::Cyan() << "\nYou can't show clients " << UI::Reset() << endl;
			}
			break;

		case MainMenuOption::AddClient:

			if (HasPermission(user, Permission::AddClient)) {

				MangerClient.AddClient(Vclients);

				// Save after modification
				fileBank.SaveDataTofile(Vclients, FileClient);

				Utils::WaitAndReturn();
			}
			else {
				cout << UI::Cyan() << "\nYou can't Add client " << UI::Reset() << endl;
			}
			break;

		case MainMenuOption::DeleteClient:

			if (HasPermission(user, Permission::DeleteClient)) {

				MangerClient.DeleteClient(Vclients);

				fileBank.SaveDataTofile(Vclients, FileClient);

				Utils::WaitAndReturn();
			}
			else {
				cout << UI::Cyan() << "\nYou can't show clients " << UI::Reset() << endl;
			}
			break;

		case MainMenuOption::UpdateClient:

			if (HasPermission(user, Permission::UpdateClient)) {

				MangerClient.UpdateClient(Vclients);

				fileBank.SaveDataTofile(Vclients, FileClient);

				Utils::WaitAndReturn();
			}
			else {
				cout << UI::Cyan() << "\nYou can't Update clients " << UI::Reset() << endl;
			}
			break;

		case MainMenuOption::FindClient:

			if (HasPermission(user, Permission::FindClient)) {

				MangerClient.SearchClient(Vclients);

				Utils::WaitAndReturn();
			}
			else {
				cout << UI::Cyan() << "\nYou can't Find clients " << UI::Reset() << endl;
			}
			break;

		case MainMenuOption::Transcations:

			if (HasPermission(user, Permission::Transcations)) {

				MangerClient.Transcations(Vclients);

				fileBank.SaveDataTofile(Vclients, FileClient);

				Utils::WaitAndReturn();
			}
			else {
				cout << UI::Cyan() << "\nYou can't Transcations " << UI::Reset() << endl;
			}
			break;

		case MainMenuOption::MangerUsers:

			if (HasPermission(user, Permission::ManageUsers)) {

				MangerUser.AllMangeUsers(VUsers, user.Permission(), user);

				fileBank.SaveDataTofile(VUsers, FileUser);
			}
			else {
				cout << UI::Cyan() << "\nYou can't Manger Users " << UI::Reset() << endl;
			}
			break;

		case MainMenuOption::Logout:

			// Re-login user
			user = MangerUser.Login(VUsers, LocationInVector);

			fileBank.SaveDataTofile(VUsers, FileUser);

			break;

		default:

			cout << UI::Magenta() << "Good Bye" << UI::Reset();

			// Save all data before exit
			fileBank.SaveDataTofile(Vclients, FileClient);
			fileBank.SaveDataTofile(VUsers, FileUser);

			again = 0;
			break;
		}
	}
}