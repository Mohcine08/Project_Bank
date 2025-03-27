#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>
using namespace std;
const string ClientsFileName = "ClientsData";
struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkClientForDelete = false;
};
enum enMainMenueOptions
{
    Show = 1, Add = 2,
     Delete =3, Update= 4, 
     Find= 5, Transactions = 6 ,
     Exit = 7
};
enum enTransactionsMenueOptions{Deposit =1 ,Withdraw =2, TotalBalance =3, MainMenue = 4};
bool ClientExistsByAccountNumber(vector<stClient> vClients, string AccountNumber)
{
    for(stClient & Client : vClients)
    {
        if(Client.AccountNumber == AccountNumber)
        {
            return true;
        }
    }
    return false;
}
stClient ReadNewClient(vector<stClient> vClients)
{
    stClient Client;
    cout << "Adding New Client:\n\n";
    cout << "Please enter a Account Number?  ";
    getline(cin >> ws , Client.AccountNumber);
    while(ClientExistsByAccountNumber(vClients,Client.AccountNumber))
    {
        cout << "Client with [" << Client.AccountNumber << "] already exists, enter another Account Number?  ";
        getline(cin, Client.AccountNumber);
    }
    cout << "Please enter a Pin Code?  ";
    getline(cin , Client.PinCode);
    cout << "Please enter a Name?  ";
    getline(cin , Client.Name);
    cout << "Please enter a phone?  ";
    getline(cin , Client.Phone);
    cout << "Please enter a Accout Balance?  ";
    cin >> Client.AccountBalance;

    return Client;
}
string ReadClientAccountNumber()
{
    string Anumber;

    cout << "Please enter a Account Number?  ";
    cin >> Anumber;
    
    return Anumber;
}
double ReadAmount(string message)
{
    double num ;
    cout << message ;
    cin >> num;
    return num;
}
char ReadAnswer(string message)
{
    char answer = 'Y';
    cout << message ;
    cin >> answer;
    return answer;
}
string ConvertRecordToLine(stClient Client, string Delim = "#//#")
{
    string DataLine = "";
    
    DataLine += Client.AccountNumber + Delim;
    DataLine += Client.PinCode + Delim;
    DataLine += Client.Name + Delim;
    DataLine += Client.Phone + Delim;
    DataLine += to_string(Client.AccountBalance);
    
    return DataLine;
}
vector<string> SplitFunction(string S , string Delim = "#//#")
{
    string word = "";
    int postion = 0;
    vector<string> vWords;
    while((postion = S.find(Delim)) != std::string::npos)
    {
        word = S.substr(0 , postion);
        if(word != "")
        {
            vWords.push_back(word);
        }
        S.erase(0 , postion + Delim.length());
    }
    if(S != "")
    {
        vWords.push_back(S);
    }
    return vWords;
}
stClient ConvertDataLineToRecord(string DataLine , string Delim = "#//#")
{
    stClient Client;
    vector<string> vClientData = SplitFunction(DataLine,Delim);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}
vector<stClient> LoadClientsDataFromFile(string FileName)
{
    string DataLine;
    stClient Client;
    vector<stClient> vClientsRecord;
    fstream MyFile;

    MyFile.open(FileName, ios::in);
    if(MyFile.is_open())
    {
        while(getline(MyFile, DataLine))
        {
            Client = ConvertDataLineToRecord(DataLine);
            vClientsRecord.push_back(Client);
        }
        MyFile.close();
    }

    return vClientsRecord;
}
void AddDataLineToFile(string FileName , string DataLine)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);
    if(MyFile.is_open())
    {
        MyFile << DataLine << endl;
        MyFile.close();
    }
}
string Tabs(short N)
{
    string t = "";
    for(short f = 0 ; f < N ; f++)
    {
        t += "\t";
    }
    return t;
}
void ShowMainMenueScrean()
{
    system("cls");

    cout << "===============================================\n";
    cout << Tabs(2) << "Main Menue Screan\n";
    cout << "===============================================\n";
    cout << Tabs(1) << "[1] Show Client List.\n";
    cout << Tabs(1) << "[2] Add New Client.\n";
    cout << Tabs(1) << "[3] Delete Client. \n";
    cout << Tabs(1) << "[4] Update Client Info. \n";
    cout << Tabs(1) << "[5] Find Client. \n";
    cout << Tabs(1) << "[6] Transactions.\n";
    cout << Tabs(1) << "[7] Exit.\n";
    cout << "===============================================\n";
}
void PrintClientRecord(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <stClient> vClients)
{
    system("cls");
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
	for (stClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "_______________________________________________________";
	cout << "_________________________________________\n" << endl;
    
}
void AddNewClient(vector<stClient> &vClients)
{
    stClient Client;
    Client = ReadNewClient(vClients);
    vClients.push_back(Client);
    AddDataLineToFile(ClientsFileName,ConvertRecordToLine(Client));
}
void AddClients(vector<stClient> &vClients)
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout <<"----------------------------------------------------------------------------\n";
        cout << Tabs(2) << "Add New Clients Screan\n";
        cout <<"----------------------------------------------------------------------------\n";

        AddNewClient(vClients);

        cout << "Client Added Seccussfully, do you want to add more clients? Y/N  ";
        cin >> AddMore;
    } while (towupper(AddMore) == 'Y');
}
void PrintClientCard(stClient Client)
{
	cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------\n";
	cout << "\nAccout Number   : " << Client.AccountNumber;
	cout << "\nPin Code        : " << Client.PinCode;
	cout << "\nName            : " << Client.Name;
	cout << "\nPhone           : " << Client.Phone;
	cout << "\nAccount Balance : " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}
bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients ,stClient &Client)
{
    for(stClient & C : vClients)
    {
        if(C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient> &vClients)
{
    for(stClient & C : vClients)
    {
        if(C.AccountNumber == AccountNumber)
        {
            C.MarkClientForDelete = true;
            return true;
        }
    }
    return false;
}
void SaveVectorToFile(string FileName,vector<stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine = "";
    if(MyFile.is_open())
    {
        for(stClient &Client : vClients)
        {
            if(Client.MarkClientForDelete == false)
            {
                DataLine = ConvertRecordToLine(Client);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
}
void DeleteClientByAccountNumber(vector<stClient> &vClients)
{
    cout << "-------------------------------------------------------------------------\n";
    cout << Tabs(2) << "Delete Client Screan\n";
    cout << "-------------------------------------------------------------------------\n\n";
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();
    char answer = 'Y';
    if(FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to delete this Client? Y/N?  ";
        cin >> answer;
        if(towupper(answer) == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber,vClients);
            SaveVectorToFile(ClientsFileName,vClients);
            
            vClients = LoadClientsDataFromFile(ClientsFileName);
        }
    }
    else
    {
        cout << "Client with Account Number [" << AccountNumber << "] Not Found! \n";        
    }
    
}
stClient ChangeClientData(string AccountNumber)
{
    stClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "Please enter a Pin Code?  ";
    getline(cin >> ws, Client.PinCode);
    cout << "Please enter a Name?  ";
    getline(cin , Client.Name);
    cout << "Please enter a phone?  ";
    getline(cin , Client.Phone);
    cout << "Please enter a Accout Balance?  ";
    cin >> Client.AccountBalance;

    return Client;
}
void UpdateClientDataByAccountNumber(vector<stClient> &vClients)
{
    cout << "-------------------------------------------------------------------------\n";
    cout << Tabs(2) << "Update Client Info Screan\n";
    cout << "-------------------------------------------------------------------------\n\n";
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();
    char answer = 'Y';
    if(FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to update this Client? Y/N?  ";
        cin >> answer;
        if(towupper(answer) == 'Y')
        {
            
            for(stClient & C : vClients)
            {
                if(C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientData(AccountNumber);
                    break;
                }
            }

            SaveVectorToFile(ClientsFileName,vClients);
            cout << "\n\n Client updeted seccussfully.\n";
        }
    }
    else
    {
        cout << "Client with Account Number [" << AccountNumber << "] Not Found! \n";        
    }
}
void FindClient(vector<stClient> vClients)
{
    cout << "-------------------------------------------------------------------------\n";
    cout << Tabs(2) << "Find Client Screan\n";
    cout << "-------------------------------------------------------------------------\n\n";
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if(FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "Client with Account Number [" << AccountNumber << "] Not Found! \n";
    }
}
void ShowEndScrean()
{
    cout << "-------------------------------------------------------------------------\n";
    cout << Tabs(2) << "Program Ends :-)\n";
    cout << "-------------------------------------------------------------------------\n\n";
    system("pause>0");
    
}
short ReadChoice(string message)
{
    short num ;
    cout << message ;
    cin >> num;
    return num;
}
void ShowTransactionsMenueScrean()
{
    system("cls");
    
    cout << "===============================================\n";
    cout << Tabs(2) << "Transactions Menue Screan\n";
    cout << "===============================================\n";
    cout << Tabs(1) << "[1] Deposit.\n";
    cout << Tabs(1) << "[2] Withdraw.\n";
    cout << Tabs(1) << "[3] TotalBalances. \n";
    cout << Tabs(1) << "[4] Main Menue. \n";
    cout << "===============================================\n";
}
void DepositFunction(vector<stClient>& vClients,string AccountNumber)
{
    double DepositAmount;
    char answer = 'Y';
    for (stClient& C : vClients)
    {
        if (AccountNumber == C.AccountNumber)
        {
            PrintClientCard(C);

            DepositAmount = ReadAmount("Please enter Deposit amount?  ");

            answer = ReadAnswer("Are you sure you want perform this Transactios?  y/n?  ");
            if (towlower(answer) == 'y')
            {
                C.AccountBalance += DepositAmount;
            }

            break;
        }
    }
    SaveVectorToFile(ClientsFileName, vClients);
}
void ShowDeposetScrean(vector<stClient> &vClients)
{
    cout << "===============================================\n";
    cout << Tabs(2) << "Deposit Screan\n";
    cout << "===============================================\n";

    string AccountNumber = ReadClientAccountNumber();
    while (!ClientExistsByAccountNumber(vClients, AccountNumber))
    {
        cout << "Client with [" << AccountNumber << "] does not exist.\n  ";
        AccountNumber = ReadClientAccountNumber();
    }
    DepositFunction(vClients,AccountNumber);
}
void WithdrawFumction(vector<stClient> &vClients ,string AccountNumber)
{
    double WithdrawAmount;
    char answer = 'Y';
    for (stClient& C : vClients)
    {
        if (AccountNumber == C.AccountNumber)
        {
            PrintClientCard(C);

            WithdrawAmount = ReadAmount("Please enter Withdraw amount?  ");

            while(C.AccountBalance < WithdrawAmount)
            {
                cout << "Amount exceeds the balance, you can withdraw up to : " << C.AccountBalance << endl;
                WithdrawAmount = ReadAmount("Please enter Withdraw amount?  ");
            }

            answer = ReadAnswer("\nAre you sure you want perform this Transactios?  y/n?  ");
            if (towlower(answer) == 'y')
            {
                C.AccountBalance -= WithdrawAmount;
            }

            break;
        }
    }
    SaveVectorToFile(ClientsFileName, vClients);
}
void ShowWithdrawScrean(vector<stClient> &vClients)
{
    cout << "===============================================\n";
    cout << Tabs(2) << "Withdraw Screan\n";
    cout << "===============================================\n";


    string AccountNumber = ReadClientAccountNumber();
    while (!ClientExistsByAccountNumber(vClients, AccountNumber))
    {
        cout << "Client with [" << AccountNumber << "] does not exist.\n  ";
        AccountNumber = ReadClientAccountNumber();
    }

    WithdrawFumction(vClients,AccountNumber);
}
double CalculToTalBalance(vector<stClient> &vClients)
{
    double total = 0;

    for(stClient &Client : vClients)
    {
        total += Client.AccountBalance;
    }
    return total;
}
void ShowTotalBalanceScrean(vector<stClient> &vClients)
{


    PrintAllClientsData(vClients);
    cout << Tabs(3) << "Total balance = " << CalculToTalBalance(vClients) << endl;
    
    
    cout << "\n Press any key to go back to Main Menue...";
    system("pause>0");
}
void PerformTransactionsMenueOption(enTransactionsMenueOptions Choice , vector<stClient> &vClients)
{
    system("cls");
    switch(Choice)
    {
        case enTransactionsMenueOptions::Deposit :
            ShowDeposetScrean(vClients);
            break;
        case enTransactionsMenueOptions::Withdraw :
            ShowWithdrawScrean(vClients);
            break;
        case enTransactionsMenueOptions::TotalBalance :
            ShowTotalBalanceScrean(vClients);
            break;
    }
}
void StartTransactionsMenue(vector<stClient> &vClients)
{
    enTransactionsMenueOptions Choice ;
    do
    {
       ShowTransactionsMenueScrean();
       Choice = (enTransactionsMenueOptions)ReadChoice("\nChoose What do you want to do? [1 to 4]?  ");
       PerformTransactionsMenueOption(Choice,vClients);

    } while (enTransactionsMenueOptions::MainMenue != Choice);
    
}
void StopScrean()
{
    cout << "\n Press any key to go back to Main Menue...";
    system("pause>0");
}
void PerformMainMenueOption(enMainMenueOptions Choice,vector<stClient> &vClients)
{
    system("cls");
    switch(Choice)
    {
        case enMainMenueOptions::Show :
            PrintAllClientsData(vClients);
            StopScrean();
            break;
        case enMainMenueOptions::Add :
            AddClients(vClients);
            StopScrean();
            break;
        case enMainMenueOptions::Delete :
            DeleteClientByAccountNumber(vClients);
            StopScrean();
            break;
        case enMainMenueOptions::Update :
            UpdateClientDataByAccountNumber(vClients);
            StopScrean();
            break;
        case enMainMenueOptions::Find :
            FindClient(vClients);
            StopScrean();
            break;
        case enMainMenueOptions::Transactions :
            StartTransactionsMenue(vClients);
            break;
        case enMainMenueOptions::Exit :
            ShowEndScrean();
            break;
    }
    
    
}
void StartProgram()
{
    enMainMenueOptions Choice;
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    do
    {
        ShowMainMenueScrean();
        Choice = (enMainMenueOptions)ReadChoice("\nChoose What do you want to do? [1 to 7]?  ");
        PerformMainMenueOption(Choice,vClients);

        
    } while (Choice != enMainMenueOptions::Exit);
}
int main()
{
   
    StartProgram();
    
    return 0;
}

