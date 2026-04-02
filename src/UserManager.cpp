#include "../include/UserManager.h"
#include <iostream>
#include <vector>
#include "../include/User.h"
#include "../include/Utils.h"
#include "../include/States.h"
#include "../include/UI.h"
#include <string>
#include "../include/FileManager.h"
#include "../include/BankSystem.h"
using namespace std;

// Handle login process (search user + validate password + retry logic)
User UserManager::Login(vector<User>& VUsears, int& location) {

	User user1;
	UI::Clear();
	cout << "============================ Login screen ============================\n\n";
	// Search for username and update location
	SearchUser(VUsears, location);
	if (location == -1 || VUsears.empty()) {

		cout << UI::Yellow() << "\n Creating new user\n\n" << UI::Reset();
		AddUser(VUsears);


		File::SaveDataTofile(VUsears, FileUser);

		cout << UI::Green() << "\nNew user created \n" << UI::Reset();
		return user1;
	}

	//   password system
	int counter = 0;

	while (true) {

		user1.SetPassword(Utils::AskUserForString("Password: "));

		
		if (VUsears[location].Password() == user1.Password()) {
			cout << UI::Green() << "\nLogin successful  Welcome \n" << UI::Reset();
			return VUsears[location];
		}

		counter++;

		cout << UI::Red() << "\nWrong password (" << counter << "/4)\n" << UI::Reset();

		// 
		if (counter < 4) {
			continue;
		}

		// After 4 Invalid input Password
		cout << UI::Cyan() << " " << UI::Reset();

		int choice = Utils::AskUserForNumber(UI::Cyan() + "\n1) Try again\n2) Change password\nChoose: " + UI::Reset(), UI::Red() + "Erorr enter 1,2" + UI::Reset(), 1, 2);
		

		if (choice == 1) {
			counter = 0; // reset
			continue;
		}
		else if (choice == 2) {
			

			VUsears[location].SetPassword(Utils::AskUserForString(UI::Cyan() + "Enter New Password: "+UI::Reset()));
			File::SaveDataTofile(VUsears, FileUser);

			cout << UI::Green() << "\nPassword updated successfully \n" << UI::Reset();
			return VUsears[location];
		}
	}
}
//// Linear search for username (case-insensitive)
bool UserManager::SearchOnUser( vector <User>& Users, string Name ,int &location) {

	for ( location = 0; location < Users.size(); location++) {
		if (Utils::ToLowerString(Users[location].UserName()) == Utils::ToLowerString(Name)) {
			return true;
		}
	}
	location = -1;
	return false;
}

// Ensure username uniqueness before creation
string UserManager::NotRepetedUserName(vector <User>& Users, int &location) {
	string s = "";
	
	while (true) {
		if (!(UserManager::SearchOnUser(Users, s = Utils::AskUserForString("User Name: "), location))) {
			return s;
		}
		else
		{
			cout << UI::Cyan() << "The user name <" << s << " > is included: " << UI::Reset() << endl;
		}
	}
	return s;
}

bool  UserManager::UserNameRepeted(string NameNew, string NameOld) {
	if (NameNew == NameOld) {
		return true;
	}
	return false;
}
string UserManager::EditUserNameAndNotRepetted(string UserNameOld) {
	string username = "";
	bool answer = true;
	while (answer) {

		username = Utils::AskUserForString("Enter User Name to edit: ");
		if ((UserNameRepeted(username, UserNameOld))) {

			answer = !(Utils::AskYesOrNo("User Name Not change are you sure ?y/n"));

		}
		else {
			return username;
			answer = false;
			
		}
	}

	return username;
}
//// Edit user data (name, password, permissions)
void UserManager::Update(vector<User>& Users, int permission) {

	int index = -1;

	if (!(permission & (int)Permission::ManageUsers)) {
		cout << UI::Cyan() << "We can't Update" << UI::Reset() << endl;
		return;
	}

	SearchUser(Users, index);

	if (index == -1) {
		cout << UI::Cyan() << "We can't Update" << UI::Reset() << endl;
		return;
	}

	User user = Users[index]; 

	while (true)
	{
		if (Utils::AskYesOrNo("Edit Name? y/n")) {
			user.SetUserName(EditUserNameAndNotRepetted(user.UserName()));
		}

		if (Utils::AskYesOrNo("Edit Password? y/n")) {
			user.SetPassword();
		}

		if (Utils::AskYesOrNo("Edit Permissions? y/n")) {
			user.SetPermision();
		}

		UI::ShowUsersHeader(1);
		UI::ShowUser(user);

		if (!Utils::AskYesOrNo("Anything else? y/n")) break;
	}

	
	Users[index] = user;

	

	cout << UI::Green() << "Update successfully ......" << UI::Reset();
}
// Create and add new user to system
void UserManager::AddUser(vector<User>& Users) {
		User user;
		int location;
		user.SetUserName(NotRepetedUserName(Users, location));
		user.SetPassword();
		user.SetPermision();
		Users.push_back(user);
		UI::ShowUsersHeader(1);
		UI::ShowUser(user);
		if (Utils::AskYesOrNo("Are you sure to Add? y/n")) {
			cout << UI::Green() << "Add successfully ......" << UI::Reset()<<endl;
		}
		else {
			cout << UI::Green() << "OK" << UI::Reset() << endl;
		}
	}
// Remove user with safety check (prevent self-delete)
void UserManager::DeletUser(vector <User>&Users ,int Location ,bool DoYouWantMassage) {
	if (Users.empty()) {
		return;
	}
		Users.erase(Users.begin() + Location);
		if (DoYouWantMassage) {
			cout << UI::Cyan() << "Delete successfully ......" << UI::Reset();
		}
	}
void UserManager::DeletUser(vector <User>& Users, User MyUser) {
		int location = 0;
		SearchUser(Users, location);
		if (Users[location].UserName() == MyUser.UserName() && location !=-1) {
			cout << UI::Red() << "You can't delete You`re self"<<UI::Reset() << endl;
			return;
		}
		else {
			UI::ShowUsersHeader(1);
			UI::ShowUser(Users[location]);
			if (Utils::AskYesOrNo("Are you sure To delete ?y/n")) {
				DeletUser(Users, location, true);
			}

		}

	}
	void UserManager::SearchUser(vector<User>& Usears ,int &location ) {
		string s = "";
		if (Usears.empty()) {
			location = -1;
			cout << UI::Yellow() << "No users found, create new user\n\n" << UI::Reset();
			return;
		}
		for(int count=1;count<=4;count++){
			if (UserManager::SearchOnUser(Usears, s=Utils::AskUserForString("User Name : "), location)) {
				
				break;
			}
			else
			{
				cout << UI::Cyan()
					<< "User <" << s << "> not found. Attempt failed ("
					<< count << "/4)"
					<< UI::Reset() << endl;
			}
			
		}

	}

	void UserManager::SearchUser(vector<User>& Usears) {
		string s = "";
		int location = 0;
		for (int count = 1; count <= 5; count++) {
			if (UserManager::SearchOnUser(Usears, s = Utils::AskUserForString("Enter User Name :"), location)) {

				UI::ShowUsersHeader(1);
				UI::ShowUser(Usears[location]);

				break;
			}
			else
			{
				cout << UI::Cyan() << "The user name <" << s << " > is not include : " << UI::Reset() << endl;
			}

		}

	}
	// Main menu loop for user management system

	void UserManager::AllMangeUsers(vector<User>& Usears, int Permissions , User user) 
	{
	
		

		while (true) {
			UI::ShowManageUsersMenu();
			ManageUsersMenuOption MUMO = static_cast<ManageUsersMenuOption>(Utils::AskUserForNumber("Waht choice from 1 to 6? ", "choice 1 to 6", 1, 6));
			switch (MUMO) {

			case ManageUsersMenuOption::ListUsers:
			
					UI::ShowUsersList(Usears);
					Utils::WaitAndReturn("Press Enter to return to Manger User .......");
		
				break;
			case ManageUsersMenuOption::AddNewUser:

				UI::PrintInPox("Add New User Screen");


					AddUser(Usears);
					Utils::WaitAndReturn("Press Enter to return to Manger User .......");
				break;
			case ManageUsersMenuOption::DeleteUser:
			
				UI::PrintInPox("Delete Users Screen");
					DeletUser(Usears, user);
					
					Utils::WaitAndReturn("Press Enter to return to Manger User.......");
				break;
			case ManageUsersMenuOption::UpdateUser:
				
				UI::PrintInPox("Update Users Screen");
					Update(Usears, Permissions);
					if (!(Permissions & (int)Permission::ManageUsers)) {
						return;
					}
					Utils::WaitAndReturn("Press Enter to return to Manger User......");
				break;
			case ManageUsersMenuOption::FindUser:
			
				UI::PrintInPox("Find User Screen");
					SearchUser(Usears);
					Utils::WaitAndReturn("Press Enter to return to Manger User.......");
				break;
			default:
				Utils::WaitAndReturn();
				
				return;
			}
		}
		
	}