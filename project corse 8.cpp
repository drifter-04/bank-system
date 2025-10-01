#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <iomanip>
using namespace std;
struct sUsers
{
	string userNume;
	string userPin;
	int userPermisstions;
	bool markForDelet = false;
};
sUsers user;
 //problem45
struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool markForDelet = false;
};
enum enMainMenuePermissions {
	eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
	pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
};
bool checkPermissions(enMainMenuePermissions permission) {
	if (permission == enMainMenuePermissions::eAll)
		return true;
	if ((permission & user.userPermisstions) == permission)
		return true;
	else return false;
}
void accessFiled() {
	cout << " you don't have permission to access this property \n";
}

sClient readClient() {
	sClient x;
	cout << "Enter Accont Number ";
	getline(cin >> ws, x.AccountNumber);
	cout << "Enter Pincode ";
	getline(cin, x.PinCode);
	cout << "Enter Name ";
	getline(cin, x.Name);
	cout << "Enter Phone ";
	getline(cin, x.Phone);
	cout << "Enter Balance ";
	cin >> x.AccountBalance;
	return x;

}
string convertClientToLine(sClient x, string dilm = "#//#") {
	string s = "";
	s = s + x.AccountNumber + dilm;
	s = s + x.PinCode + dilm;
	s = s + x.Name + dilm;
	s = s + x.Phone + dilm;
	s = s + to_string(x.AccountBalance) + dilm;
	return s;
}
vector<string> splitString(string s, string delim) {
	vector<string> V1;
	short pos = 0;
	string sWord;
	while ((pos = s.find(delim)) != std::string::npos) {
		sWord = s.substr(0, pos);
		if (sWord != "")
			V1.push_back(sWord);
		s.erase(0, pos + delim.length());
	}
	if (s != "") {
		V1.push_back(s);
	}
	return V1;
}
sClient readRecordStringConvertToRecord(string s, string dilm = "#//#") {
	sClient c;
	vector<string> x = splitString(s, "#//#");
	c.AccountNumber = x[0];
	c.PinCode = x[1];
	c.Name = x[2];
	c.Phone = x[3];
	c.AccountBalance = stod(x[4]);
	return c;
}
void printRecord(sClient x) {
	cout << "Account Number  : " << x.AccountNumber << endl;
	cout << "pin Code        : " << x.PinCode << endl;
	cout << "Name            : " << x.Name << endl;
	cout << "Phone           : " << x.Phone << endl;
	cout << "Account Balance : " << x.AccountBalance << endl;

}
void addClientToFile(string fileName, string dataLine) {
	fstream file;
	file.open(fileName, ios::out | ios::app);
	file << dataLine << endl;
	file.close();
}
void addClient() {
	sClient client = readClient();
	addClientToFile("emad.txt", convertClientToLine(client));

}
void addClients() {
	char x = 'Y';
	do {
		system("cls");
		cout << "adding new client \n\n";
		addClient();
		cout << "do you need to add more ?\n";
		cin >> x;
	} while (toupper(x) == 'Y');
}
//problem48
vector<sClient> fechClintsFromFill(string File= "emad.txt") {
	vector<sClient> x;
	fstream file;
	sClient client;
	string line;
	file.open( File, ios::in);
	while (getline(file, line)) {
		client = readRecordStringConvertToRecord(line);
		x.push_back(client);
	}
	file.close();
	return x;
}
void printClinetRecord(sClient oneClient) {
	cout << '|' << setw(15) << left << oneClient.AccountNumber;
	cout << '|' << setw(10) << left << oneClient.PinCode;
	cout << '|' << setw(40) << left << oneClient.Name;
	cout << '|' << setw(10) << left << oneClient.Phone;
	cout << '|' << setw(10) << left << oneClient.AccountBalance;
}
void printAllClients(vector<sClient> records) {
	if (!checkPermissions(enMainMenuePermissions::pListClients)) {
		accessFiled();
		return;
	}
	cout << "\n\t\t\t\t\tClient List (" << records.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << '|' << left << setw(15) << "AccountNumber";
	cout << '|' << left << setw(10) << "PinCode";
	cout << '|' << left << setw(40) << "Name";
	cout << '|' << left << setw(10) << "Phone";
	cout << '|' << left << setw(10) << "AccountBalance";
	cout << endl;
	for (sClient& x : records) {
		printClinetRecord(x);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
//problem49
string readClientAccontNumber() {
	cout << "Enter user accont number:\t";
	string number;
	cin >> number;
	return number;
}
bool serchForClient(string accontNumber, vector<sClient> clients, sClient& C) {
	for (sClient& x : clients) {
		if (x.AccountNumber == accontNumber) {
			C = x;
			return true;

		}
	}return false;

}
void printClientInfo(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}
//problem50
//mySol::
vector<sClient> deletUser(string AccontNumber, vector<sClient> fechedVector) {
	vector<sClient> newRecord;
	for (sClient& x : fechedVector) {
		if (AccontNumber != x.AccountNumber)
			newRecord.push_back(x);
	}return newRecord;
}
void saveDataToFile(vector<sClient> v) {
	fstream file;
	file.open("emad.txt", ios::out);
	for (sClient& x : v) {

		file << convertClientToLine(x) << endl;
	}
	file.close();
}
//proSol::
const string fileName = "emad.txt";
bool markForDelet(string accontNumber, vector<sClient>& v) {
	for (sClient& x : v) {
		if (accontNumber == x.AccountNumber) {

			x.markForDelet = true;
			return true;
		}
	}return false;
}

vector<sClient> saveDataToFile(string fileName, vector<sClient> v) {
	fstream file;
	file.open(fileName, ios::out | ios::trunc);
	if (file.is_open()) {
		for (sClient& x : v) {
			if (x.markForDelet == false) {
				file << convertClientToLine(x) << endl;
			}

		}
		file.close();
	}

	return v;
}
bool deletClaintFromFile(string accontNumber, vector<sClient>& v) {
	sClient C;
	char YN = 'n';
	if (serchForClient(accontNumber, v, C)) {
		printClientInfo(C);
		cout << "\nare you sure to delet user? (Y/N)\t";
		cin >> YN;
		if (YN == 'Y' || YN == 'y') {
			markForDelet(accontNumber, v);
			saveDataToFile(fileName, v);
			v = fechClintsFromFill();
			return true;
		}
		else {
			cout << "cancled\n";
			return false;
		}
	}
	else {
		cout << "no user have " << accontNumber << " as accont number\n";
		return false;
	}
}
//problem51
bool updateClient(string accontNumber, vector<sClient>& client) {
	sClient C;
	char YN = 'n';
	if (serchForClient(accontNumber, client, C)) {
		cout << "are you sure to update user whos accont number is " << accontNumber << endl;
		printClientInfo(C);
		cout << "Yes or No (Y/N)\n";
		cin >> YN;

		if (YN == 'Y' || YN == 'y') {
			for (sClient& x : client) {
				if (accontNumber == x.AccountNumber) {
					x = readClient();

					break;
				}

			}
			saveDataToFile(fileName, client);
			cout << "the User sucsesfully updated\n";
			return true;
		}
		else {
			cout << "operation canceled\n";
			return false;
		}

	}
	else {
		cout << "no mach for user have accont number " << accontNumber << endl;
		return false;
	}
}
/// <summary>
/// project for corse 7
/// </summary>
void mainMenueSecren();
void goToMianMenue() {
	cout << "press any key to retarn to mian ..";
	system("pause>0");
	mainMenueSecren();
}
void addNewclientSecren() {
	if (!checkPermissions(enMainMenuePermissions::pAddNewClient)) {
		accessFiled();
		return;
	}
	cout << "****************************************\n";
	cout << "        add New client Secren           \n";
	cout << "****************************************\n";
	addClient();
	system("pause>0");


}
void deleteClaintSecren() {
	if (!checkPermissions(enMainMenuePermissions::pDeleteClient)) {
		accessFiled();
		return;
	}
	cout << "****************************************\n";
	cout << "         delete client Secren           \n";
	cout << "****************************************\n";
	vector<sClient> x = fechClintsFromFill();
	deletClaintFromFile(readClientAccontNumber(), x);


}
void updateClientSecren() {
	if (!checkPermissions(enMainMenuePermissions::pUpdateClients)) {
		accessFiled();
		return;
	}
	cout << "****************************************\n";
	cout << "         update client Secren           \n";
	cout << "****************************************\n";
	vector<sClient> v = fechClintsFromFill();
	updateClient(readClientAccontNumber(), v);

}
void serchForClientSecren() {
	if (!checkPermissions(enMainMenuePermissions::pFindClient)) {
		accessFiled();
		return;
	}
	cout << "****************************************\n";
	cout << "         find client Secren           \n";
	cout << "****************************************\n";
	sClient C;
	vector<sClient> v = fechClintsFromFill();
	if (serchForClient(readClientAccontNumber(), v, C))
		printClientInfo(C);
	else {
		cout << "can't find client\n";
	}
}
/// <summary>
/// project 2 for corse 7
/// </summary>
/// <param name="choice"></param>
void deposit(string accontNumber, vector<sClient>& v) {
	sClient C;
	char YN = 'n';
	if (serchForClient(accontNumber, v, C)) {
		 
		printClientInfo(C);
		cout << "\nenter the amont \n";
		int numberOfDepostion = 0;
		cin >> numberOfDepostion;
		cout << "\nAre you sure to depos to this user?\n";
		cout << "\n (Y||N)\n";
		cin >> YN;
		if (YN == 'y' || YN == 'Y') {
			 
			for (sClient& x : v) {
				if (x.AccountNumber == accontNumber)
					x.AccountBalance += numberOfDepostion;
			}
			saveDataToFile(v);
			cout << "Deposit successfully\n";
		}
		else {
			cout << "Canceled\n";
		}
	}
	else cout << "did not found user\n";
}
void depositSecren() {
	cout << "****************************************\n";
	cout << "          Deposit Secern                \n";
	cout << "****************************************\n";
	vector<sClient> v = fechClintsFromFill();

	deposit(readClientAccontNumber(), v);
	 
	
}
void Withdraw(string accontNumber, vector<sClient>& v) {
	sClient C;
	char YN = 'n';
	if (serchForClient(accontNumber, v, C)) {

		printClientInfo(C);
		cout << "\nenter the amont \n";
		int numberOfDepostion = 0;
		cin >> numberOfDepostion;
		cout << "\nAre you sure to Withdraw from this user?\n";
		cout << "\n (Y||N)\n";
		cin >> YN;
		if (YN == 'y' || YN == 'Y') {

			for (sClient& x : v) {
				if (x.AccountNumber == accontNumber)
					x.AccountBalance -= numberOfDepostion;
			}
			saveDataToFile(v);
			cout << "Withdraw successfully\n";
		}
		else {
			cout << "Canceled\n";
		}
	}
	else cout << "did not found user\n";
}
void WithdrawSecren() {
	cout << "****************************************\n";
	cout << "          Withdraw Secern                \n";
	cout << "****************************************\n";
	vector<sClient> v = fechClintsFromFill();

	Withdraw(readClientAccontNumber(), v);


}
void printClinetBalancesRecord(sClient oneClient) {
	cout << '|' << setw(15) << left << oneClient.AccountNumber;
	cout << '|' << setw(40) << left << oneClient.Name;
	cout << '|' << setw(10) << left << oneClient.AccountBalance;
}
void printAllClientsBalances(vector<sClient> records) {
	cout << "\n\t\t\t\t\tClient List (" << records.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << '|' << left << setw(15) << "AccountNumber";

	cout << '|' << left << setw(40) << "Name";

	cout << '|' << left << setw(10) << "AccountBalance";
	cout << endl;
	for (sClient& x : records) {
		printClinetBalancesRecord(x);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void printTotalBalances(vector<sClient> v) {
	cout << "\n\t\t\t\t\tTotal Balances (" << v.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << '|' << left << setw(15) << "AccountNumber";

	cout << '|' << left << setw(40) << "Name";

	cout << '|' << left << setw(10) << "AccountBalance";
	cout << endl;
	int TotalBalances = 0;
	for (sClient& x : v) {
		printClinetBalancesRecord(x);
		TotalBalances+= x.AccountBalance;
		cout << endl;
	}
	cout << "\n_______________________________________";
	cout << "Total Balances " << TotalBalances;
	cout << "_________________________________________\n" << endl;
}
 
void userChoiceForTransaction(int choice) {
	switch (choice)
	{
	case 1:
		system("cls");
		depositSecren();
		goToMianMenue();
		break;
	case 2:
		system("cls");
		WithdrawSecren();
		goToMianMenue();
		break;
	case 3:
		system("cls");
		printAllClientsBalances(fechClintsFromFill());
		goToMianMenue();
		break;
	case 4:
		goToMianMenue();
	default:
		break;
	}
}

void printUserRecord(sUsers oneUser) {
	cout << '|' << setw(15) << left <<  oneUser.userNume;
	cout << '|' << setw(10) << left << oneUser.userPin;
	cout << '|' << setw(40) << left << oneUser.userPermisstions;
	 
}
void printAllUsers(vector<sUsers> records) {
	cout << "\n\t\t\t\t\tClient List (" << records.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << '|' << left << setw(15) << "User Name";
	cout << '|' << left << setw(10) << "Pin Code";
	cout << '|' << left << setw(40) << "User Permisstions";
	cout << endl;;
	 
	cout << endl;
	for (sUsers& x : records) {
		printUserRecord(x);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}



void transactionSecren() {
	if (!checkPermissions(enMainMenuePermissions::pTranactions)) {
		accessFiled();
		return;
	}
	system("cls");
	cout << "****************************************\n";
	cout << "          Transaction Secrean           \n";
	cout << "****************************************\n";
	cout << "\t[1] Deposit \n";
	cout << "\t[2] Withdraw \n";
	cout << "\t[3] Total Balances \n";
	cout << "\t[4] Main Menue \n";
	 
	int x = 0;
	cin >> x;
	if (x <= 4 && x >= 1)
		userChoiceForTransaction(x);
	else {
		cout << " invaled input try agian ";
		system("pause>0");
		mainMenueSecren();

	}
}
void mangeUserSecren();
void login();
void userChoice(int choice) {
    switch (choice)
    {
    case 1:
        system("cls");
        printAllClients(fechClintsFromFill());
        goToMianMenue();
        break;
    case 2:
        system("cls");
        addNewclientSecren();
        goToMianMenue();
        break;
    case 3:
        system("cls");
        deleteClaintSecren();
        goToMianMenue();
        break;
    case 4:
        system("cls");
        updateClientSecren();
        goToMianMenue();
        break;
    case 5:
        system("cls");
        serchForClientSecren();
        goToMianMenue();
        break;
	case 6:
		system("cls");
		transactionSecren();
		goToMianMenue();
		break;
	case 7:
		system("cls");
		mangeUserSecren();
		goToMianMenue();
	case 8:
		system("cls");
		login();
		 
    default:
        break;
    }
}
void mainMenueSecren() {
	system("cls");
	cout << "****************************************\n";
	cout << "          Main menu Screen           \n";
	cout << "****************************************\n";
	cout << "\t[1] show client list \n";
	cout << "\t[2] add new client \n";
	cout << "\t[3] delete client\n";
	cout << "\t[4] update client information\n";
	cout << "\t[5] find client\n";
	cout << "\t[6] transactions\n";
	cout << "\t[7] Mange Users\n";
	cout << "\t[8] logout\n";
	int x = 0;
	cin >> x;
	if (x <= 8 && x >= 1)
		userChoice(x);
	else {
		cout << " invaled input try agian ";
		system("pause>0");
		mainMenueSecren();

	}
}
/// <summary>
/// project 8 (1)
/// </summary>

const string fileUsers = "User.txt";
bool serchForUserForLogin (string userName, string userPin, vector<sUsers> users, sUsers& C) {
	for (sUsers& x : users) {
		if (x.userNume == userName) {
			if (x.userPin == userPin) {
				C = x;
				return true;
			}

		}
	}return false;

}
bool serchForUser(string userName, vector<sUsers> users, sUsers& C) {
	for (sUsers& x : users) {
		 
			if (x.userNume == userName ) {
				C = x;
				return true;
			}

		 
	}return false;

}
sUsers readRecordStringConvertToRecordForUsers(string s, string dilm = "#//#") {
	sUsers c;
	vector<string> x = splitString(s, "#//#");
	c.userNume = x[0];
	c.userPin= x[1];
	c.userPermisstions=stoi(x[2]);
	
	return c;
}
vector<sUsers> fechUsersFromFill(string File = "User.txt") {
	vector<sUsers> x;
	fstream file;
	sUsers client;
	string line;
	file.open(File, ios::in);
	while (getline(file, line)) {
		client = readRecordStringConvertToRecordForUsers(line);
		x.push_back(client);
	}
	file.close();
	return x;
}
 
 
void goToMangeUserMaune() {
	cout << "press any key to retarn to mian ..";
	system("pause>0");
	mangeUserSecren();
}
void printUserInfo(sUsers Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\nUser Name        : " << Client.userNume;
	cout << "\nPin Code         : " << Client.userPin;
	cout << "\nUser Permisstions:"<<Client.userPermisstions;
	 
}
bool markUserForDelet(string userName, vector<sUsers>& v) {
	for (sUsers& x : v) {
		if (userName == x.userNume) {

			x.markForDelet = true;
			return true;
		}
	}return false;
}
string convertUserToLine(sUsers x, string dilm = "#//#") {
	string s = "";
	s = s + x.userNume + dilm;
	s = s + x.userPin + dilm;
	s = s + to_string(x.userPermisstions)+ dilm;
	
	 
	return s;
}
void saveUsersDataToFile(vector<sUsers> v) {
	fstream file;
	file.open(fileUsers, ios::out);
	for (sUsers& x : v) {

		file << convertUserToLine(x) << endl;
	}
	file.close();
}
vector<sUsers> saveUsersDataToFile(string fileName, vector<sUsers> v) {
	fstream file;
	file.open(fileName, ios::out | ios::trunc);
	if (file.is_open()) {
		for (sUsers& x : v) {
			if (x.markForDelet == false) {
				file << convertUserToLine(x) << endl;
			}

		}
		file.close();
	}

	return v;
}
bool deletUserFromFile(string userName, vector<sUsers>& v) {
	sUsers C;
	char YN = 'n';
	if (serchForUser(userName, v, C)) {
		printUserInfo(C);
		cout << "\nare you sure to delete user? (Y/N)\t";
		cin >> YN;
		if (YN == 'Y' || YN == 'y') {
			markUserForDelet(userName, v);
			saveUsersDataToFile(fileUsers,v);
			v = fechUsersFromFill(fileUsers);
			return true;
			
		}
		else {
			cout << "canceled\n";
			return false;
		}
	}
	else {
		cout << "no user have " << userName << " as account number\n";
		return false;
	}
}
string readUserAccontNumber(){
	string x;
	cout << "Enter user name \n";
	cin >> x;
	return x;
}
string readUserPassword() {
	string x;
	cout << "Enter user password\n";
	cin >> x;
	return x;
}
void deleteUserSecren() {
	cout << "****************************************\n";
	cout << "         Delete User Secren           \n";
	cout << "****************************************\n";
	vector<sUsers> x = fechUsersFromFill(fileUsers);
	string a = readUserAccontNumber();
	deletUserFromFile(a,x);
}
int readUserPermisstions() {
	int permisstionSum = 0;
	char YN = 'N';
	cout << "do you wont to give full permisstions ? (Y|N)\t";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		return -1;
	}
	cout << "do you wont to give access to \n";
	cout << "show client list ?(Y|N)\t";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		permisstionSum += enMainMenuePermissions::pListClients;
	}
	cout << "Add New Client ?";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		permisstionSum += enMainMenuePermissions::pAddNewClient;
	}
	cout << "Delete Client ?";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		permisstionSum += enMainMenuePermissions::pDeleteClient;
	}
	cout << "Update Client ?";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		permisstionSum += enMainMenuePermissions::pUpdateClients;
	}
	cout << "Find Client ?";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		permisstionSum += enMainMenuePermissions:: pFindClient;
	}
	cout << "Transactions ?";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		permisstionSum += enMainMenuePermissions::pTranactions;
	}
	cout << "Mange Users ?";
	cin >> YN;
	if (YN == 'Y' || YN == 'y') {
		permisstionSum += enMainMenuePermissions::pManageUsers;
	}
	return permisstionSum;
}
sUsers readUser() {
	sUsers x;
	cout << "Enter User Name \t";
	getline(cin >> ws, x.userNume);
	cout << "Enter User PIN code \t";
	getline(cin, x.userPin);
	x.userPermisstions = readUserPermisstions();
	return x;
}
void addUserToFile(string fileUsers, string dataLine) {
	fstream file;
	file.open(fileUsers, ios::out | ios::app);
	file << dataLine << endl;
	file.close();
	
}
void addNewUser() {
	sUsers user;
	user = readUser();
	addUserToFile(fileUsers,convertUserToLine(user));
	
}
void addNewUserSecren() {
	cout << "****************************************\n";
	cout << "           Add User Secren           \n";
	cout << "****************************************\n";
	addNewUser();
}
bool updateUser(string userName, vector<sUsers>& user) {
	sUsers C;
	char YN = 'n';
	if (serchForUser(userName, user, C)) {
		cout << "are you sure to update user who have account number is " << userName << endl;
		printUserInfo(C);
		cout << "Yes or No (Y/N)\n";
		cin >> YN;

		if (YN == 'Y' || YN == 'y') {
			for (sUsers& x : user) {
				if (userName == x.userNume) {
					x = readUser();

					break;
				}

			}
			saveUsersDataToFile(fileUsers, user);
			cout << "the User successfully updated\n";
			return true;
		}
		else {
			cout << "operation canceled\n";
			return false;
		}

	}
	else {
		cout << "no mach for user have account number " << userName << endl;
		return false;
	}
}
void updateUserSecren() {
	cout << "****************************************\n";
	cout << "           Update User Secren           \n";
	cout << "****************************************\n";
	vector<sUsers> v = fechUsersFromFill();
	updateUser(readUserAccontNumber(), v);
}
void serchForUserSecren() {
	cout << "****************************************\n";
	cout << "         find client Secren           \n";
	cout << "****************************************\n";
	sUsers C;
	vector< sUsers> v = fechUsersFromFill();
	if (serchForUser(readUserAccontNumber(), v, C))
		printUserInfo(C);
	else {
		cout << "can't find User\n";
	}
}

void mangeUserChoice(int choice) {
	switch (choice)
	{
	case 1:
		system("cls");
		printAllUsers(fechUsersFromFill("User.txt"));
		goToMangeUserMaune();
		break;
	case 2:
		system("cls");
		addNewUserSecren();
		goToMangeUserMaune();
		break;
	case 3:
		system("cls");
		deleteUserSecren();
		goToMangeUserMaune();
	case 4:
		system("cls");
		updateUserSecren();
		goToMangeUserMaune();
		break;
	case 5:
		system("cls");
		serchForUserSecren();
		goToMangeUserMaune();
	case 6:
		goToMianMenue();
	default:
		break;
	}
}
void mangeUserSecren() {
	if (!checkPermissions(enMainMenuePermissions::pManageUsers)) {
		accessFiled();
		return;
	}
	system("cls");
	cout << "****************************************\n";
	cout << "          Mange User Secrean           \n";
	cout << "****************************************\n";
	cout << "\t[1] List Users\n";
	cout << "\t[2] Add New User\n";
	cout << "\t[3] Delete user\n";
	cout << "\t[4] Update User\n";
	cout << "\t[5] Find User\n";
	cout << "\t[6] Main Menu\n";

	int x = 0;
	cin >> x;
	if (x <= 6 && x >= 1)
		mangeUserChoice(x);
	else {
		cout << " invaled input try agian ";
		system("pause>0");
		mainMenueSecren();

	}

}
void login() {
	bool loginFilled = false;
	do { 
		system("cls");
		cout << "****************************************\n";
		cout << "             login Secren               \n";
		cout << "****************************************\n";
		if (loginFilled) cout << "wrong password or user name \n";
		cout << "Enter User name \t";
		cin >> user.userNume;
		cout << endl;
		cout << "Enter user PIN\t";
		cin >> user.userPin;
		cout << endl;
		loginFilled = !serchForUserForLogin(user.userNume, user.userPin, fechUsersFromFill(fileUsers), user);

	} while (loginFilled);
	mainMenueSecren();
}
 
int main() {
	login();
	 
}
