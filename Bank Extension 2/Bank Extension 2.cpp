#include<iostream>
#include <string>
#include<fstream>
#include<cctype>
#include<vector>
#include<iomanip>
#include <limits>
using namespace std;

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
	etMainMenu = 4

};

enum enPermissions {

	pAll = -1,
	pClientList = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactions = 32,
	pManageUsers = 64

};

enum enManageUsersMenu {

	eListUser = 1,
	eAddNewUsers = 2,
	eDeleteUsers = 3,
	eUpdateUsers = 4,
	eFindUsers = 5,
	emMainMenu = 6

};

const string ClientsFileName = "Client.txt";
const string UsersFileName = "Users.txt";

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

sUser CurrentUser;

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

sClient ConvertLineToRecord(string Line, string Delim = "#//#") {

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

sUser ConvertUserLineToRecord(string Line, string Delim = "#//#") {

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

vector<sClient>LoadClientsFromFile(const string& FileName) {

	fstream MyFile;
	vector<sClient>vClients;
	sClient Client;
	string Line = "";

	MyFile.open(FileName, ios::in);

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

vector<sUser>LoadUsersFromFile(const string&FileName) {

	fstream MyFile;
	vector<sUser>vUsers;
	sUser User;
	string Line = "";

	MyFile.open(FileName, ios::in);

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

void AddClientToFile(const sClient& Client,const string &FileName) {

	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << ConvertRecordToLine(Client) << endl;

		MyFile.close();
	}

}

void AddUserToFile(sUser const& User,const string &FileName) {

	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << ConvertRecordToLine(User) << endl;

		MyFile.close();
	}

}

void SaveUsersToFile(vector<sUser>const& vUsers, const string &FileName) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {

		for (sUser const& User : vUsers) {

			if (!User.MarkToDelete) {
				MyFile << ConvertRecordToLine(User) << endl;
			}

		}
		MyFile.close();
	}

}

void SaveClientsToFile(vector<sClient> const& vClients,const string &FileName) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);

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

	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(20) << Client.Name;
	cout << "| " << left << setw(15) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance << " |";
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

bool FindUserByUserNameAndPassword(vector<sUser> const &vUsers,const string& UserName, const string& Password) {

	for (const sUser& User : vUsers) {

		if (User.UserName == UserName && User.Password == Password) {
			CurrentUser = User;
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
	AddClientToFile(Client,ClientsFileName);

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
		return enPermissions::pAll;
	}

	cout << "\n\nDo you want to give access to : ";

	cout << "\n\nShow Client List ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::pClientList;
	}

	cout << "\n\nAdd New Users ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::pAddNewClient;
	}

	cout << "\n\nDelete Users  ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::pDeleteClient;
	}

	cout << "\n\nUpdate Users ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::pUpdateClient;
	}

	cout << "\n\nFind Client ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::pFindClient;
	}

	cout << "\n\nTransactions ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::pTransactions;
	}

	cout << "\n\nManage Users ? y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permission = Permission | enPermissions::pManageUsers;
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

bool CheckAccsessPermissons(short UserPermission, enPermissions PermissionToCheck) {

	if (UserPermission == enPermissions::pAll) {
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
	AddUserToFile(User,UsersFileName);

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
			SaveClientsToFile(vClients,ClientsFileName);

			vClients = LoadClientsFromFile(ClientsFileName);

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

void MarkUserToDeleteByUserName(string UserName, vector<sUser>& vUsers) {

	for (sUser& User : vUsers) {

		if (User.UserName == UserName) {
			User.MarkToDelete = true;
		}

	}

}

bool DeleteUserByUserName(const string& UserName, vector<sUser>& vUsers) {

	sUser User;
	char Answer = 'n';

	if (IsUserExistByUserName(UserName, vUsers, User)) {

		if (User.UserName == "Admin" || User.UserName == "admin") {
			cout << "\n\nCannot Delete this user, it is the System Admin!\n";
			return false;
		}

		PrintUserDetails(User);

		cout << "\n\nAre You Sure You Want To Delete This User ? y/n ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			MarkUserToDeleteByUserName(UserName, vUsers);
			SaveUsersToFile(vUsers,UsersFileName);
			vUsers = LoadUsersFromFile(UsersFileName);
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

			SaveClientsToFile(vClients,ClientsFileName);

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

sUser ChangeUserRecord(string& UserName) {

	sUser User;
	char Answer = 'n';

	User.UserName = UserName;

	cout << "\n\nEnter Password ? ";
	cin >> User.Password;

	User.Permission = ReadPermissionToSet();

	return User;
}

bool UpdateUserByUserName(const string& UserName, vector<sUser>& vUsers) {

	sUser MyUser;
	char Answer = 'n';

	if (IsUserExistByUserName(UserName, vUsers, MyUser)) {

		PrintUserDetails(MyUser);

		cout << "\n\nAre You Sure You Want To Update This User ? y/n ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			for (sUser& User : vUsers) {

				if (User.UserName == UserName) {

					User = ChangeUserRecord(User.UserName);
					break;
				}

			}

			SaveUsersToFile(vUsers,UsersFileName);

			cout << "\nUser Updated Successfully.";
			return true;
		}
		return false;
	}
	else {

		cout << "\nUser With User Name (" << UserName << ") Is Not Found! \n";
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

void FindUserByUserName(const string& UserName, vector<sUser>const& vUsers) {

	sUser User;

	if (IsUserExistByUserName(UserName, vUsers, User)) {

		PrintUserDetails(User);

	}
	else {
		cout << "\nUser With User Name (" << UserName << ") Is Not Found! \n";
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
				SaveClientsToFile(vClients,ClientsFileName);
				cout << "\nDone successfully new balance is : " << Client.AccountBalance;

				break;
			}

		}

	}

}

void ShowAllClientsScreen(vector<sClient>const& vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n____________________________________________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(20) << "Client Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(12) << "Balance" << " |";

	cout << "\n____________________________________________________________________________________\n" << endl;

	if (vClients.size() == 0) {

		cout << "\n\t\t\t\tNo Clients Available In The System!\n";

	}
	else {

		for (const sClient& Client : vClients) {

			PrintClientRecord(Client);

		}

	}

	cout << "\n____________________________________________________________________________________\n" << endl;

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

	cout << "\n_________________________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(25) << "Client Name";
	cout << "| " << left << setw(12) << "Balance" << " |";

	cout << "\n_________________________________________________________________\n" << endl;

	if (vClients.size() == 0) {

		cout << "\t\t\t\tNo Clients Available In The System!";

	}
	else {

		for (sClient& Client : vClients) {

			TotalBalances += Client.AccountBalance;

			cout << "| " << left << setw(15) << Client.AccountNumber;
			cout << "| " << left << setw(25) << Client.Name;
			cout << "| " << left << setw(12) << Client.AccountBalance << " |";

			cout << endl;

		}

		cout << "\n_________________________________________________________________\n" << endl;

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

void ShowAddNewUsersScreen(vector<sUser>& vUsers) {

	cout << "\n----------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n----------------------------------\n";
	cout << "Adding New User : \n\n";

	AddNewUsers(vUsers);

}

void ShowDeleteUsersScreen(vector<sUser>& vUsers) {

	cout << "\n----------------------------------\n";
	cout << "\tDelete Users Screen";
	cout << "\n----------------------------------\n\n";

	DeleteUserByUserName(ReadUserName(), vUsers);

}

void ShowUpdateUserScreen(vector<sUser>& vUsers) {

	cout << "\n----------------------------------\n";
	cout << "\tUpdate Users Screen";
	cout << "\n----------------------------------\n\n";

	UpdateUserByUserName(ReadUserName(), vUsers);

}

void ShowFindUserScreen(vector<sUser>const& vUsers) {

	cout << "\n----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n----------------------------------\n\n";

	FindUserByUserName(ReadUserName(), vUsers);

}

void ShowLoginScreen() {

	cout << "\n----------------------------------\n";
	cout << "\tLogin Screen";
	cout << "\n----------------------------------\n";

}

void ShowTransactions(vector <sClient> &vClients,vector <sUser> &vUsers); 

void ShowManageUsers(vector<sUser>& vUsers, vector<sClient>& vClients);

void ShowMainMenu(vector<sClient>& vClients, vector<sUser>& vUsers);

void ShowAccessDeniedMessage() {

	cout << "\n----------------------------------\n";
	cout << "Access Denied,\n"
		<< "You Don't Have Permission To Do This,\n"
		<< "Please Contact Your Admin.";
	cout << "\n----------------------------------\n";
	cout << "\nPress Any Key To Go Back To Main Menu ...";
	system("pause>0");

}

bool Login(vector<sUser>& vUsers, vector<sClient>& vClients);

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
	cout << "\t[6] Main Menu.\n";
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
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Log Out.\n";

	cout << "=============================================\n";

}

void ShowManageUsers(vector<sUser>& vUsers, vector<sClient>& vClients) {

	while (true) {

		ShowManageUsersTable();

		enManageUsersMenu Option = (enManageUsersMenu)ReadChoice(1, 6);

		switch (Option) {

		case enManageUsersMenu::eListUser:
			system("cls");
			ShowAllUsersTable(vUsers);
			cout << "\nPress any key to go back to manage users menu...";
			system("pause>nul");

			break;

		case enManageUsersMenu::eAddNewUsers:
			system("cls");
			ShowAddNewUsersScreen(vUsers);
			cout << "\nPress any key to go back to manage users menu...";
			system("pause>nul");

			break;

		case enManageUsersMenu::eDeleteUsers:
			system("cls");
			ShowDeleteUsersScreen(vUsers);
			cout << "\nPress any key to go back to manage users menu...";
			system("pause>nul");

			break;

		case enManageUsersMenu::eUpdateUsers:
			system("cls");
			ShowUpdateUserScreen(vUsers);
			cout << "\nPress any key to go back to manage users menu...";
			system("pause>nul");

			break;

		case enManageUsersMenu::eFindUsers:
			system("cls");
			ShowFindUserScreen(vUsers);
			cout << "\nPress any key to go back to manage users menu...";
			system("pause>nul");

			break;

		case enManageUsersMenu::emMainMenu:
			
			return;

		}

	}

}

void ShowTransactions(vector<sClient>& vClients , vector<sUser>& vUsers) {

	while (true) {

		ShowTransactionsTable();

		enTranactionsOptions Option = (enTranactionsOptions)ReadChoice(1, 4);

		switch (Option) {

		case enTranactionsOptions::eDeposit:

			system("cls");
			ShowDepositScreen(vClients);
			cout << "\nPress any key to go back to transactios menu...";
			system("pause>nul");

			break;

		case enTranactionsOptions::eWithdraw:

			system("cls");
			ShowWithdrawScreen(vClients);
			cout << "\nPress any key to go back to transactios menu...";
			system("pause>nul");

			break;

		case enTranactionsOptions::eTotalBalance:

			system("cls");
			ShowAllTotalBalanceScreen(vClients);
			cout << "\nPress any key to go back to transactios menu...";
			system("pause>nul");

			break;

		case enTranactionsOptions::etMainMenu:

			return;

		}

	}

}

void ShowMainMenu(vector<sClient>& vClients, vector<sUser>& vUsers) {

	while (true) {

		ShowMainMenuTable();
		enMainMenuOptions Option = (enMainMenuOptions)ReadChoice(1, 8);

		switch (Option) {

		case enMainMenuOptions::eListClients:

			system("cls");
			if (CheckAccsessPermissons(CurrentUser.Permission, enPermissions::pClientList)) {

				ShowAllClientsScreen(vClients);
				cout << "\nPress Any Key To Go Back To Main Menu ...";
				system("pause>0");

			}
			else {
				ShowAccessDeniedMessage();
			}

			break;

		case enMainMenuOptions::eAddNewClient:

			system("cls");
			if (CheckAccsessPermissons(CurrentUser.Permission, enPermissions::pAddNewClient)) {

				ShowAddNewClientsScreen(vClients);
				cout << "\nPress Any Key To Go Back To Main Menu ...";
				system("pause>0");

			}
			else {
				ShowAccessDeniedMessage();
			}

			break;

		case enMainMenuOptions::eDeleteClient: {

			system("cls");
			if (CheckAccsessPermissons(CurrentUser.Permission, enPermissions::pDeleteClient)) {

				ShowDeleteClientScreen(vClients);
				cout << "\nPress Any Key To Go Back To Main Menu ...";
				system("pause>0");

			}
			else {
				ShowAccessDeniedMessage();
			}

			break;

		}

		case enMainMenuOptions::eUpdateClient: {

			system("cls");
			if (CheckAccsessPermissons(CurrentUser.Permission, enPermissions::pUpdateClient)) {

				ShowUpdateClientInfoScreen(vClients);
				cout << "\nPress Any Key To Go Back To Main Menu ...";
				system("pause>0");

			}
			else {
				ShowAccessDeniedMessage();
			}

			break;

		}

		case enMainMenuOptions::eFindClient: {

			system("cls");
			if (CheckAccsessPermissons(CurrentUser.Permission, enPermissions::pFindClient)) {

				ShowFindClientScreen(vClients);
				cout << "\nPress Any Key To Go Back To Main Menu ...";
				system("pause>0");

			}
			else {
				ShowAccessDeniedMessage();
			}

			break;

		}

		case enMainMenuOptions::eTransactions:

			system("cls");
			if (CheckAccsessPermissons(CurrentUser.Permission, enPermissions::pTransactions)) {
				ShowTransactions(vClients, vUsers);
			}
			else {
				ShowAccessDeniedMessage();
			}

			break;

		case enMainMenuOptions::eManageUsers:

			system("cls");
			if (CheckAccsessPermissons(CurrentUser.Permission, enPermissions::pManageUsers)) {
				ShowManageUsers(vUsers, vClients);
			}
			else {
				ShowAccessDeniedMessage();
			}

			break;

		case enMainMenuOptions::eLogout:

			system("cls");
			Login(vUsers, vClients);

			break;

		}

	}

}

bool Login(vector<sUser>& vUsers, vector<sClient>& vClients) {

	sUser User;
	short MaxAttempts = 3;
	short Attempt = 0;

	ShowLoginScreen();

	while (Attempt < MaxAttempts) {

		cout << "Enter User Name : ";
		getline(cin >> ws, User.UserName);

		cout << "\nEnter Password : ";
		getline(cin >> ws, User.Password);

		if (FindUserByUserNameAndPassword(vUsers, User.UserName, User.Password)) {
			ShowMainMenu(vClients, vUsers);
			return true;
		}

		Attempt++;
		cout << "Invalid UserName/Password Attempts Left "
			<< (MaxAttempts - Attempt) << "\n";

		if (Attempt < MaxAttempts) {

			cout << "\nPress any key to try again...";
			system("pause>0");
			system("cls");
			ShowLoginScreen();

		}

	}

	cout << "\nYou are locked out after 3 failed attempts.\n";
	return false;
}

int main()
{
	vector<sClient> vClients = LoadClientsFromFile(ClientsFileName);
	vector<sUser>vUsers = LoadUsersFromFile(UsersFileName);

	Login(vUsers, vClients);

	system("pause>0");

	return 0;
}