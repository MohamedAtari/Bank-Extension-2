#include<iostream>
#include <string>
#include<fstream>
#include<cctype>
#include<vector>
#include<iomanip>
#include <limits>
using namespace std;

const string ClientsFileName = "Client.txt";
const string UsersFileName = "Users.txt";

enum enMainMenuOptions {

	eListClients = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransactions = 6,
	eManageUsers = 7,
	eLogout = 8

};

enum enTranactionsOptions {

	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalance = 3,
	eMainMenu = 4

};

enum enPermissions {

	eAll = -1,
	eClientList = 1,
	eAddNewClient = 2,
	eDeleteClient = 4,
	eUpdateClient = 8,
	eFindClient = 16,
	eTransactions = 32,
	eManageUsers = 64

};

enum enManageUsersMenu {

	UsersList = 1,
	


};

struct sClient {

	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkToDelete = false;

};

struct sUser {

	string UserName = "";
	string Password = "";
	short Permission = 0;
	bool MarkToDelete = false;

};

vector<string> SplitString(string Line, string Delim) {

	vector<string> vString;
	size_t Pos = 0;

	while ((Pos = Line.find(Delim)) != string::npos) {

		vString.push_back(Line.substr(0, Pos));
		Line.erase(0, Pos + Delim.length());

	}

	vString.push_back(Line);

	return vString;
}

sClient ConvertLineToRecord(string Line, string Delim = "#//#"){

	sClient Client;

	vector<string>vClientData = SplitString(Line, Delim);

	if (vClientData.size() >= 5) {

		Client.AccountNumber = vClientData[0];
		Client.PinCode = vClientData[1];
		Client.Name = vClientData[2];
		Client.Phone = vClientData[3];
		Client.AccountBalance = stod(vClientData[4]);

	}
	return Client;
}

sUser ConvertUserLineToRecord(string Line,string Delim = "#//#") {

	vector<string>vString = SplitString(Line, Delim);
	sUser User;

	if (vString.size() == 3) {

		User.UserName = vString[0];
		User.Password = vString[1];
		User.Permission = stoi(vString[2]);

	}

	return User;
}

string ConvertRecordToLine(const sClient& Client, string Delim = "#//#") {

	string Line = "";

	Line = Client.AccountNumber + Delim;
	Line += Client.PinCode + Delim;
	Line += Client.Name + Delim;
	Line += Client.Phone + Delim;
	Line += to_string(Client.AccountBalance);

	return Line;
}

string ConvertRecordToLine(const sUser& User, string Delim = "#//#") {

	string Line = "";

	Line = User.UserName + Delim;
	Line += User.Password + Delim;
	Line += to_string(User.Permission);

	return Line;
}

vector<sClient>LoadClientsFromFile() {

	fstream MyFile;
	vector<sClient>vClients;
	sClient Client;
	string Line = "";

	MyFile.open(ClientsFileName, ios::in);

	if (MyFile.is_open()) {

		while (getline(MyFile, Line)) {

			if (Line != "") {
				Client = ConvertLineToRecord(Line);
				vClients.push_back(Client);
			}

		}

		MyFile.close();

	}
	return vClients;
}

vector<sUser>LoadUsersFromFile() {

	fstream MyFile;
	vector<sUser>vUsers;
	sUser User;
	string Line = "";

	MyFile.open(UsersFileName, ios::in);

	if (MyFile.is_open()) {

		while (getline(MyFile, Line)) {

			User = ConvertUserLineToRecord(Line);
			vUsers.push_back(User);

		}
		MyFile.close();
	}

	return vUsers;
}

bool IsUserExistByUserName(string UserName, vector<sUser>const& vUsers, sUser& User);

void AddClientToFile(const sClient& Client) {

	fstream MyFile;

	MyFile.open(ClientsFileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << ConvertRecordToLine(Client) << endl;

		MyFile.close();
	}

}

void AddUserToFile(sUser const& User) {

	fstream MyFile;

	MyFile.open(UsersFileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << ConvertRecordToLine(User) << endl;

		MyFile.close();
	}

}

void SaveUsersToFile(vector<sUser>const& vUsers) {

	fstream MyFile;

	MyFile.open(UsersFileName, ios::out);

	if (MyFile.is_open()) {

		for (sUser const& User : vUsers) {

			if (!User.MarkToDelete) {
				MyFile << ConvertRecordToLine(User) << endl;
			}

		}
		MyFile.close();
	}

}

void SaveClientsToFile(vector<sClient> const& vClients) {

	fstream MyFile;

	MyFile.open(ClientsFileName, ios::out);

	if (MyFile.is_open()) {

		for (const sClient& Client : vClients) {

			if (!Client.MarkToDelete) {
				MyFile << ConvertRecordToLine(Client) << endl;
			}

		}
		MyFile.close();
	}

}

void PrintClientRecord(sClient const& Client) {

	cout << "|" << left << setw(16) << Client.AccountNumber;
	cout << "|" << left << setw(12) << Client.PinCode;
	cout << "|" << left << setw(20) << Client.Name;
	cout << "|" << left << setw(17) << Client.Phone;
	cout << "|" << left << setw(16) << Client.AccountBalance;
	cout << endl;

}

void PrintUserRecord(sUser const& User) {

	cout << "|" << left << setw(17) << User.UserName;
	cout << "|" << left << setw(12) << User.Password;
	cout << "|" << left << setw(14) << User.Permission;
	cout << endl;

}

void PrintClientDetails(const sClient& Client) {
	cout << "\nThe Following Are The Client Details : ";
	cout << "\n-------------------------------";
	cout << "\nAccount Number  : " << Client.AccountNumber;
	cout << "\nPin Code        : " << Client.PinCode;
	cout << "\nName            : " << Client.Name;
	cout << "\nPhone Number    : " << Client.Phone;
	cout << "\nAccount Balance : " << Client.AccountBalance;
	cout << "\n-------------------------------\n\n";
}

void PrintUserDetails(const sUser& User) {

	cout << "\n\nThe folowing are the user details\n";
	cout << "-----------------------------------";
	cout << "\nUser Name  : " << User.UserName;
	cout << "\nPassword   : " << User.Password;
	cout << "\nPermission : " << User.Permission;
	cout << "\n-----------------------------------";

}

double ReadPositiveNumber(string Message) {

	double Number = 0;

	while (true) {

		cout << Message;
		cin >> Number;

		if (!cin.fail() && Number >= 0) {
			break;
		}

		cout << "\nInvalid Input Please Enter A Number. \n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}

	return Number;
}

short ReadChoice(short From, short To) {

	short Choice = From - 1;

	while (true) {

		cout << "Enter what do you want to do? [" << From << "-" << To << "]? ";
		cin >> Choice;

		if (!cin.fail() && (Choice <= To && Choice >= From)) {
			break;
		}

		cout << "\nInvalid Input Please Enter A Number. \n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}

	return Choice;
}

string ReadAccountNumber() {

	string AccountNumber = "";

	cout << "Enter Account Number ? ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}

string ReadUserName() {

	string UserName = "";
	cout << "Enter User Name ? ";
	getline(cin >> ws, UserName);
	return UserName;

}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>const& vClients, sClient& Client) {

	for (const sClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}

	}

	return false;
}

bool IsUserExistByUserName(string UserName, vector<sUser>const& vUsers, sUser& User) {

	for (sUser const& U : vUsers) {

		if (U.UserName == UserName) {
			User = U;
			return true;
		}

	}
	return false;
}

sClient ReadNewClient(vector<sClient>const& vClients) {

	sClient Client;
	sClient TempClient;

	Client.AccountNumber = ReadAccountNumber();

	while (FindClientByAccountNumber(Client.AccountNumber, vClients, TempClient)) {

		cout << "\nClient With [" << Client.AccountNumber << "] Already Exists, Enter Anthor Account Number : ";
		getline(cin >> ws, Client.AccountNumber);

	}

	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone Number ? ";
	getline(cin, Client.Phone);

	Client.AccountBalance = ReadPositiveNumber("Enter Account Balance ? ");

	return Client;
}

void AddNewClient(vector<sClient>& vClients) {
	sClient Client = ReadNewClient(vClients);
	vClients.push_back(Client);
	AddClientToFile(Client);

}

void AddNewClients(vector<sClient>& vClients) {

	char Confirm = 'n';

	do {

		AddNewClient(vClients);

		cout << "\nDo You Want To Add More Client (y/n) : ";
		cin >> Confirm;

	} while (toupper(Confirm) == 'Y');

}

short ReadPermissionToSet() {

	short Permission = 0;
	char Answer = 'n';

	cout << "\n\nDo You Want To Give Full Access ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		return enPermissions::eAll;
	}

	cout << "\n\nDo you want to give access to : ";

	cout << "\n\nShow Client List ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::eClientList;
	}

	cout << "\n\nAdd New Users ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::eAddNewClient;
	}

	cout << "\n\nDelete Users  ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::eDeleteClient;
	}

	cout << "\n\nUpdate Users ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::eUpdateClient;
	}

	cout << "\n\nFind Client ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::eFindClient;
	}

	cout << "\n\nTransactions ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::eTransactions;
	}

	cout << "\n\nManage Users ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::eManageUsers;
	}

	return Permission;
}

sUser ReadNewUser(vector<sUser>& Users) {

	sUser User;
	sUser Temp;

	User.UserName = ReadUserName();

	while (IsUserExistByUserName(User.UserName, Users, Temp)) {

		cout << "\nUser with [" << User.UserName << "] already exists , Enter anthor User Name ? ";
		getline(cin >> ws, User.UserName);

	}

	cout << "Enter Password ? ";
	getline(cin >> ws, User.Password);

	User.Permission = ReadPermissionToSet();

	return User;
}

bool CheckAccsessPermissons(short UserPermission,enPermissions PermissionToCheck) {

	if (UserPermission == enPermissions::eAll) {
		return true;
	}

	if ((UserPermission & PermissionToCheck) == PermissionToCheck) {
		return true;
	}

	return false;
}

void AddNewUser(vector<sUser>& Users) {

	sUser User = ReadNewUser(Users);
	Users.push_back(User);
	AddUserToFile(User);

}

void AddNewUsers(vector<sUser>& Users) {

	char AddMore = 'n';

	do {

		AddNewUser(Users);
		cout << "\n\nUser Added Successfully, do you want to add more users ? Y/N ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

void MarkClientToDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients) {

	for (sClient& Client : vClients) {

		if (Client.AccountNumber == AccountNumber) {
			Client.MarkToDelete = true;
			break;
		}

	}

}

bool DeleteClientsByAccountNumber(string AccountNumber, vector<sClient>& vClients) {

	sClient Client;
	char Confirm = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientDetails(Client);

		cout << "\nAre You Sure You Want To Delete This Client (y/n) : ";
		cin >> Confirm;

		if (toupper(Confirm) == 'Y') {

			MarkClientToDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsToFile(vClients);

			vClients = LoadClientsFromFile();

			cout << "\n\nClient Deleted Successfully. \n\n";

			return true;
		}

		return false;
	}
	else {

		cout << "\nClient With Account Number (" << AccountNumber << ") Is Not Found! \n";
		return false;

	}

}

void MarkUserToDeleteByUserName(string UserName,vector<sUser>&vUsers) {

	for (sUser& User : vUsers) {
		 
		if (User.UserName == UserName) {
			User.MarkToDelete = true;
		}

	}

}

bool DeleteUserByUserName(const string &UserName,vector<sUser>& vUsers) {

	sUser User;
	char Answer = 'n';

	if (IsUserExistByUserName(UserName, vUsers, User)) {

		if (User.UserName == "Admin" || User.UserName == "admin") {
			cout << "\n\nCannot Delete this user, it is the System Admin!\n";
			return false;
		}

		PrintUserDetails(User);

		cout << "\n\n\nAre you sure you want to delete this user ? y/n ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			MarkUserToDeleteByUserName(UserName, vUsers);
			SaveUsersToFile(vUsers);
			vUsers = LoadUsersFromFile();
			cout << "\n\nUser Deleted Successfully.\n";

			return true;
		}


	}
	else {

		cout << "\nUser With User Name (" << UserName << ") Is Not Found! \n";

	}
	return false;
}

sClient ChangeClientRecord(string AccountNumber) {

	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone Numebr ? ";
	getline(cin, Client.Phone);

	Client.AccountBalance = ReadPositiveNumber("Enter Account Balance ? ");

	return Client;
}

bool UpdateClientByAccountNumber(const string& AccountNumber, vector<sClient>& vClients) {

	sClient Client;
	char Confirm = 'y';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientDetails(Client);

		cout << "Are You Sure You Want To Update This Client ? (y/n) : ";
		cin >> Confirm;

		if (toupper(Confirm) == 'Y') {

			for (sClient& C : vClients) {

				if (C.AccountNumber == AccountNumber) {

					C = ChangeClientRecord(AccountNumber);
					break;

				}

			}

			SaveClientsToFile(vClients);

			cout << "\n\nClinet Updated Successfully";

			return true;
		}

		return false;
	}
	else {

		cout << "\nClient With Account Number (" << AccountNumber << ") Is Not Found! \n";
		return false;

	}

}

void FindClientByAccountNumberScreen(string AccountNumber, vector<sClient>const& vClints) {

	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClints, Client)) {

		PrintClientDetails(Client);

	}
	else {

		cout << "\nClient With Account Number (" << AccountNumber << ") Is Not Found! \n";

	}

}

void DepositBalnceForClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients) {

	char Confirm = 'y';

	cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
	cin >> Confirm;

	if (toupper(Confirm) == 'Y') {

		for (sClient& Client : vClients) {

			if (Client.AccountNumber == AccountNumber) {

				Client.AccountBalance += Amount;
				SaveClientsToFile(vClients);
				cout << "\nDone successfully new balance is : " << Client.AccountBalance;

				break;
			}

		}

	}

}

void ShowAllClientsScreen(vector<sClient>const& vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0) {

		cout << "\n\t\t\t\tNo Clients Available In The System!\n";

	}
	else {

		for (const sClient& Client : vClients) {

			PrintClientRecord(Client);
			cout << endl;

		}

	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

void ShowAddNewClientsScreen(vector<sClient>& vClients) {

	cout << "-------------------------------------\n";
	cout << "\tAdd New Client Screen";
	cout << "\n-------------------------------------\n";

	AddNewClients(vClients);

}

void ShowDeleteClientScreen(vector<sClient>& vClients) {

	cout << "-------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-------------------------------------\n";

	DeleteClientsByAccountNumber(ReadAccountNumber(), vClients);

}

void ShowUpdateClientInfoScreen(vector<sClient>& vClients) {

	cout << "-------------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-------------------------------------\n";

	UpdateClientByAccountNumber(ReadAccountNumber(), vClients);

}

void ShowFindClientScreen(vector<sClient>& vClients) {

	cout << "-------------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-------------------------------------\n";

	FindClientByAccountNumberScreen(ReadAccountNumber(), vClients);

}

void ShowDepositScreen(vector<sClient>& vClients) {

	cout << "-----------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-----------------------------------\n";

	sClient Client;
	string AccountNumber = ReadAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		cout << "\nClient With [" << AccountNumber << "] does not exist.\n\n";
		AccountNumber = ReadAccountNumber();

	}

	double Amount = ReadPositiveNumber("Please enter deposit amount? ");

	PrintClientDetails(Client);
	DepositBalnceForClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithdrawScreen(vector<sClient>& vClients) {

	cout << "-----------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-----------------------------------\n";

	string AccountNumber = ReadAccountNumber();
	sClient Client;

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		cout << "\nClient With [" << AccountNumber << "] does not exist.\n\n";
		AccountNumber = ReadAccountNumber();

	}

	double Amount = ReadPositiveNumber("Please enter withdraw amount? ");

	while (Client.AccountBalance < Amount) {

		cout << "\n\nAmount exceeds the balanc ,you can withdraw up to " << Client.AccountBalance << endl;

		Amount = ReadPositiveNumber("Please enter withdraw amount? ");

	}

	PrintClientDetails(Client);
	DepositBalnceForClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowAllTotalBalanceScreen(vector<sClient>& vClients) {

	double TotalBalances = 0;

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "|" << left << setw(15) << "Account Numebr";
	cout << "|" << left << setw(40) << "Client Name";
	cout << "|" << left << setw(15) << "Balance";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0) {

		cout << "\t\t\t\tNo Clients Available In The System!";

	}
	else {

		for (sClient& Client : vClients) {

			TotalBalances += Client.AccountBalance;

			cout << "|" << left << setw(15) << Client.AccountNumber;
			cout << "|" << left << setw(40) << Client.Name;
			cout << "|" << left << setw(15) << Client.AccountBalance;

			cout << endl;

		}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t\t\tTotal Balances = " << TotalBalances << endl;

	}

}

void ShowAllUsersTable(vector<sUser> const& vUsers) {

	system("cls");

	cout << "\t\t\tUsers List (" << vUsers.size() << ") User(s).\n";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "|" << left << setw(17) << "User Name";
	cout << "|" << left << setw(12) << "Password";
	cout << "|" << left << setw(14) << "Permissions";
	cout << endl;

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vUsers.size() == 0) {
		cout << "\n\t\t\tNo Users Available In The System!\n";
	}
	else {

		for (sUser const& User : vUsers) {

			PrintUserRecord(User);

		}

	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

void ShowAddNewUsersScreen(vector<sUser>& Users) {

	cout << "\n\n----------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n----------------------------------\n";
	cout << "Adding New User : \n\n";

	AddNewUsers(Users);

}

void ShowTransactions(vector<sClient>& vClients);

void ShowMainMenu(vector<sClient>& vClients);

void ShowManageUsersTable() {

	system("cls");

	cout << "============================================";
	cout << "\n\t\tManage Users Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu\n";
	cout << "============================================\n";

}

void ShowTransactionsTable() {

	system("cls");

	cout << "===========================================\n";
	cout << "\t\tTranactions Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "===========================================\n";

}

void ShowMainMenuTable() {

	system("cls");

	cout << "=============================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "=============================================\n";

	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";

	cout << "=============================================\n";

}

void GoBackToTransactions(vector<sClient>& vClients) {

	cout << "\nPress any key to go back to transactios menu...";
	system("pause>nul");
	ShowTransactions(vClients);

}

void PerformTransactions(enTranactionsOptions Option, vector<sClient>& vClients) {

	switch (Option) {

	case enTranactionsOptions::eDeposit:

		system("cls");
		ShowDepositScreen(vClients);
		GoBackToTransactions(vClients);

		break;

	case enTranactionsOptions::eWithdraw:

		system("cls");
		ShowWithdrawScreen(vClients);
		GoBackToTransactions(vClients);

		break;

	case enTranactionsOptions::eTotalBalance:

		system("cls");
		ShowAllTotalBalanceScreen(vClients);
		GoBackToTransactions(vClients);

		break;

	case enTranactionsOptions::eMainMenu:

		ShowMainMenu(vClients);

	}

}

void ShowTransactions(vector<sClient>& vClients) {

	ShowTransactionsTable();

	PerformTransactions((enTranactionsOptions)ReadChoice(1, 4), vClients);

}

void GoBackToMainMenu(vector<sClient>& vClients) {

	cout << "\nPress Any Key To Go Back To Main Menu ...";

	system("pause>0");

	ShowMainMenu(vClients);

}

void PerformMainMenuOptions(enMainMenuOptions Option, vector<sClient>& vClients,vector<sUser>&Users,sUser const &User) {

	switch (Option) {

	case enMainMenuOptions::eListClients:

		system("cls");
		if(CheckAccsessPermissons(User.Permission,enPermissions::eClientList))
		ShowAllClientsScreen(vClients);
		GoBackToMainMenu(vClients);

		break;

	case enMainMenuOptions::eAddNewClient:

		system("cls");
		if(CheckAccsessPermissons(User.Permission,enPermissions::eAddNewClient))
		ShowAddNewClientsScreen(vClients);
		GoBackToMainMenu(vClients);

		break;

	case enMainMenuOptions::eDeleteClient: {

		system("cls");
		if(CheckAccsessPermissons(User.Permission,enPermissions::eDeleteClient))
		ShowDeleteClientScreen(vClients);
		GoBackToMainMenu(vClients);

		break;

	}

	case enMainMenuOptions::eUpdateClient: {

		system("cls");
		if(CheckAccsessPermissons(User.Permission,enPermissions::eUpdateClient))
		ShowUpdateClientInfoScreen(vClients);
		GoBackToMainMenu(vClients);

		break;

	}

	case enMainMenuOptions::eFindClient: {

		system("cls");
		if (CheckAccsessPermissons(User.Permission, enPermissions::eFindClient))
		ShowFindClientScreen(vClients);
		GoBackToMainMenu(vClients);

		break;

	}

	case enMainMenuOptions::eTransactions:

		system("cls");
		if (CheckAccsessPermissons(User.Permission, enPermissions::eTransactions))
		ShowTransactions(vClients);

		break;

	case enMainMenuOptions::eManageUsers:

		system("cls");


	case enMainMenuOptions::eLogout:

		system("cls");
		

		break;

	}

}

void ShowMainMenu(vector<sClient>& vClients) {

	ShowMainMenuTable();
	PerformMainMenuOptions((enMainMenuOptions)ReadChoice(1, 7), vClients);

}

int main()
{
	vector<sClient> vClients = LoadClientsFromFile();

	ShowMainMenu(vClients);

	system("pause>0");

	return 0;
}