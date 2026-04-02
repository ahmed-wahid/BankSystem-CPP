#pragma once
enum class MainMenuOption {
    ShowClients = 1,
    AddClient,
    DeleteClient,
    UpdateClient,
    FindClient,
    Transcations,
    MangerUsers,
    Logout
};
enum class TransactionsMenuOption {
    Deposit = 1,
    Withdraw,
    TotalBalances,
    ChangeAccountNumber,
    MainMenu
};

enum class  currentUserRole {
    VIEWER = 17,
    
    ADMIN=127

};

enum class PermissionRole {
    VIEWER = 2,
    ADMIN = 1,
    custom = 3
};
enum class Permission {
    ShowClients = 1,
    AddClient = 2,
    DeleteClient = 4,
    UpdateClient = 8,
    FindClient = 16,
    Transcations = 32,
    ManageUsers = 64
};
enum class ManageUsersMenuOption {
    ListUsers = 1,
    AddNewUser,
    DeleteUser,
    UpdateUser,
    FindUser,
    MainMenu
};