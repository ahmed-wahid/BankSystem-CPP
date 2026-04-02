#include "../include/Utils.h"
#include "../include/User.h"
#include <string.h>
#include "../include/States.h"
using namespace std;

// Prompt user to enter username from console
void User::SetUserName() {
	_UserName = Utils::AskUserForString("User Name:");
}

// Return current username
string User::UserName() {
	return _UserName;
}

// Prompt user to enter password from console
void User::SetPassword() {
	_Password = Utils::AskUserForString("Password : ");
}

// Return current password
string User::Password() {
	return _Password;
}

// Set username directly (used when loading from file or system)
void User::SetUserName(string UserName) {
	_UserName = UserName;
}

// Set password directly (used when loading from file or system)
void User::SetPassword(string Password) {
	_Password = Password;
}

// Set permission value directly (bitmask)
void User::SetPermision(int Permmision) {
	_Permissions = Permmision;
}

// Return permission bitmask
int User::Permission() const {
	return _Permissions;
}

// Convert vector<string> (e.g. from file line split) to User object
// Expected format: [username, password, permission]
User User::ConvertStringFromVectorToUser(vector<string> s) {
	User c;

	c.SetUserName(s[0]);
	c.SetPassword(s[1]);

	// Convert permission string to integer
	c.SetPermision(Utils::ConvertStringToint(s[2]));

	return c;
}

// Ask user to choose permissions (Admin / Viewer / Custom)
void User::SetPermision() {

	int PermissionNumber = 0;

	// Ask user for permission type (1 == admin, 2==viewer ,3==customer)
	PermissionRole Perm = static_cast<PermissionRole>(Utils::AskUserForNumber("Select permissions:\n\n[1] Full Access\n[2] Viewer(Read Only)\n[3] Custom\n\nChoice : ","Erorr choice from 1 to 3: ",1, 3));

	switch (Perm) {

	case PermissionRole::ADMIN:
		// Assign full admin permissions 
		//currentUserRole::ADMIN ==127
		PermissionNumber = (int)currentUserRole::ADMIN;
		break;

	case PermissionRole::VIEWER:
		// Assign read-only permissions
		//currentUserRole::VIEWER means Show client and find client=17 
		PermissionNumber = (int)currentUserRole::VIEWER;
		break;

	default:
		// Custom permission selection using bitmask flags

		if (Utils::AskYesOrNo("Do you want to show clients? y/n")) {
			PermissionNumber |= (int)Permission::ShowClients;
		}

		if (Utils::AskYesOrNo("Do you want to add clients? y/n")) {
			PermissionNumber |= (int)Permission::AddClient;
		}

		if (Utils::AskYesOrNo("Do you want to delete clients? y/n")) {
			PermissionNumber |= (int)Permission::DeleteClient;
		}

		if (Utils::AskYesOrNo("Do you want to update clients? y/n")) {
			PermissionNumber |= (int)Permission::UpdateClient;
		}

		if (Utils::AskYesOrNo("Do you want to find clients? y/n")) {
			PermissionNumber |= (int)Permission::FindClient;
		}

		if (Utils::AskYesOrNo("Do you want to access transactions? y/n")) {
			PermissionNumber |= (int)Permission::Transcations;
		}

		if (Utils::AskYesOrNo("Do you want to manage users? y/n")) {
			PermissionNumber |= (int)Permission::ManageUsers;
		}
	}

	// Store final computed permission bitmask
	_Permissions = PermissionNumber;
}