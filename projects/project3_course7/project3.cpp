/*
project 1 :  bank1 :

[1] : show client list
[2] : add new client
[3] : Delete new Client
[4] : update client info
[5] :find client
[6] : exit
*/

#include <iostream>
#include "lib/myLib.h"
#include <cctype>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdexcept>
using namespace std;
const string separator = "#/";

struct stClient
{

    string accountNumber;
    string pinCode;
    string name;
    string phone;
    float accountBalance;
};
const string fileName = "project1.txt";

// --------------------------- print page Section  Function--------------------------------

void printSectionTitle(string title)
{
    cout << "\n----------------------------------\n";
    cout << "        " << title << "     \n";
    cout << "----------------------------------\n\n";
}

// ------------------------------upload data To vector functions ----------------------------------------------
vector<string> getSplitStringWordToVector(string str, string delim = ::separator)
{
    vector<string> vstr;
    short counter = 0;
    short pos = 0;
    string word;

    while ((pos = str.find(delim)) != string::npos)
    {

        vstr.push_back(str.substr(0, pos));

        str.erase(0, pos + delim.length());
    }

    // counts the last word :
    if (str != "")
        vstr.push_back(str);

    return vstr;
}

stClient lineClientDateToRecord(string lineData, string separator = ::separator)
{

    stClient Record;

    vector<string> vRecord = getSplitStringWordToVector(lineData);

    Record.accountNumber = vRecord[0];
    Record.pinCode = vRecord[1];
    Record.name = vRecord[2];
    Record.phone = vRecord[3];
    Record.accountBalance = stof(vRecord[4]);
    return Record;
}

vector<stClient> loadClientsToVector(string fileName = ::fileName)
{

    fstream ClientsFile;
    vector<stClient> vClients;
    ClientsFile.open(fileName, ios::out | ios::in);

    if (ClientsFile.is_open())
    {

        string dataLine = "";
        while (getline(ClientsFile, dataLine))
        {

            stClient client = lineClientDateToRecord(dataLine);
            vClients.push_back(client);
        }
        ClientsFile.clear();
        return vClients;
    }
    else
    {
        cerr << "Opening File Error :  ";
        exit(1);
    }
}

// ------------------------------------update file functions -----------------------------------------------
string RecordToLineClientDate(stClient client, string delim = ::separator)
{

    string str = client.accountNumber + delim + client.pinCode + delim + client.name + delim + client.phone + delim + to_string(client.accountBalance);

    return str;
}
void UpdateFile(vector<stClient> vClients, string fileName = ::fileName)
{

    fstream clientsFile;

    clientsFile.open(fileName, ios::out);

    for (int i = 0; i < vClients.size(); i++)
    {
        clientsFile << RecordToLineClientDate(vClients[i]) << endl;
    }

    clientsFile.close();
}
// ---------------------------------------------------- AddNewClients Functions :-----------------------------------------------------------------------------------------//
enum enIsClientFound
{
    notFound,
    isFound
};
enIsClientFound checkIfClientAlreadyExist(vector<stClient> &vClients, string ClientAn)
{

    for (stClient &c : vClients)
    {
        if (c.accountNumber == ClientAn)
        {
            return enIsClientFound::isFound;
        }
    }

    return enIsClientFound::notFound;
}
stClient ReadClient(vector<stClient> vClients)
{

    stClient client;
    enIsClientFound AlreadyExist = enIsClientFound::notFound;
    cout << "Adding New Client : \n\n";

    do
    {
        if (AlreadyExist)
            cout << "\nClient with [" << client.accountNumber << "]"
                 << " already exits\n";

        client.accountNumber = input::readString("Enter Account Number? ");
        AlreadyExist = checkIfClientAlreadyExist(vClients, client.accountNumber);

    } while (AlreadyExist == enIsClientFound::isFound);

    client.pinCode = input::readString("Enter PinCode? ");
    client.name = input::readString("Enter Name? ");
    client.phone = input::readString("Enter Phone? ");
    client.accountBalance = input::readFloat("Enter AccountBalance? ");

    return client;
}

void addClient(vector<stClient> &vClient)
{

    stClient client = ReadClient(vClient);
    vClient.push_back(client);
}
enum enWannaAddMore
{
    no,
    yes
};
enWannaAddMore checkIfUserWannaAddMoreRecord()
{
    char wannaAddMore;
    cout << "\nClient Successfully, do you want to add more clients";

    wannaAddMore = input::readCharacter("[y][n] : ");

    if (wannaAddMore == 'y' || wannaAddMore == 'Y')
        return enWannaAddMore::yes;

    return enWannaAddMore::no;
}

void AddClients(vector<stClient> &vClient, string fileName = ::fileName)
{
    enWannaAddMore wannaAddMore = enWannaAddMore::no;
    do
    {
        system("cls");
        printSectionTitle("Add New Clients Screen ");
        addClient(vClient);
        wannaAddMore = checkIfUserWannaAddMoreRecord();

    } while (wannaAddMore == enWannaAddMore::yes);

    UpdateFile(vClient);
}

// -------------------------------------show Client list  functions ----------------------------- :

void printClientsBasicTableOnScreen(vector<stClient> vClients)
{

    cout << setw(75) << "\n\n                                          Client List (" << vClients.size() << ") Client(s).\n";
    cout << setw(75) << "_______________________________________________________________________________________________________________________\n\n";
    cout << "  | " << left << setw(20) << "Account Name"
         << "   "
         << "  | " << left << setw(20) << "Pin Code"
         << "   "
         << "  | " << left << setw(20) << "Name"
         << "   "
         << "  | " << left << setw(10) << "phone"
         << "   "
         << "  | " << fixed << setprecision(2) << "   Balance"
         << "\n";
    cout << setw(75) << "_______________________________________________________________________________________________________________________\n\n";
}
void printClient(stClient client)
{

    cout << "  | " << left << setw(20) << client.accountNumber << "   "
                                                                  "  | "
         << left << setw(20) << client.pinCode << "   "
         << left << setw(3) << "  | " << setw(20) << client.name << "   "

         << "  | " << left << setw(10) << client.phone << "   "
                                                          "  | "
         << fixed << setprecision(2) << "   " << client.accountBalance
         << "\n";
}

void printClients(vector<stClient> vClients)
{

    system("cls");
    printClientsBasicTableOnScreen(vClients);
    for (stClient &client : vClients)
    {
        printClient(client);
    }

    cout << setw(75) << "\n_______________________________________________________________________________________________________________________\n\n";
}

// ----------------------------------------delete functions------------------------------------------------------
enIsClientFound checkIfClientAlreadyExist(vector<stClient> vClients, string ClientAn, stClient &MyClient)
{

    string dataLine = "";
    for (stClient c : vClients)
    {
        if (c.accountNumber == ClientAn)
        {
            MyClient = c;
            return enIsClientFound::isFound;
        }
    }

    return enIsClientFound::notFound;
}
void printRecord(stClient client)
{

    cout << "\n";

    cout << "Account Number  : " << client.accountNumber << "\n";
    cout << "Account PinCode : " << client.pinCode << "\n";
    cout << "Account Name    : " << client.name << "\n";
    cout << "Account Phone   : " << client.phone << "\n";
    cout << "Account Balance : " << fixed << setprecision(2) << client.accountBalance << "\n";

    cout << "\n";
}

void deleteRecordFromVector(vector<stClient> &vClients, string ClientAn)
{

    for (int i = 0; i < vClients.size(); i++)
    {
        if (vClients[i].accountNumber == ClientAn)
        {

            vClients.erase(vClients.begin() + i);
            return;
        }
    }
}
void deleteClient(vector<stClient> &vClients)
{
    system("cls");
    printSectionTitle("delete Clients Screen ");
    stClient client;

    string ClientAn = input::readString("Enter AccountNumber? ");
    if (checkIfClientAlreadyExist(vClients, ClientAn, client) == enIsClientFound::isFound)
    {

        printRecord(client);

        char sureToDelete = input::readCharacter("\nAre you sure you want delete this element? y/n ?");
        if (toupper(sureToDelete) == 'Y')
        {
            deleteRecordFromVector(vClients, ClientAn);
            UpdateFile(vClients);
            cout << "Client deleted with Successfully \n";
        }
        else
        {
            cout << "Operation Canceled with success\n";
        }
    }
    else
    {
        cout << "\nclient with Account Number(" << ClientAn << ") "
             << "not found!\n\n";
    }
}

// ---------------------- update client functions --------------------------------------------

void ReadUpdatedClient(stClient &client)
{

    client.pinCode = input::readString("Enter PinCode? ");
    client.name = input::readString("Enter Name? ");
    client.phone = input::readString("Enter Phone? ");
    client.accountBalance = input::readFloat("Enter AccountBalance? ");
}

void updateRecordFromVector(vector<stClient> &vClients, string ClientAn)
{

    for (int i = 0; i < vClients.size(); i++)
    {
        if (vClients[i].accountNumber == ClientAn)
        {
            ReadUpdatedClient(vClients[i]);
            return;
        }
    }
}
void Update(vector<stClient> &vClients)
{

    system("cls");
    printSectionTitle("Update Clients Screen ");
    stClient client;

    string ClientAn = input::readString("Enter AccountNumber? ");
    if (checkIfClientAlreadyExist(vClients, ClientAn, client) == enIsClientFound::isFound)
    {

        printRecord(client);

        char sureToDelete = input::readCharacter("\nAre you sure you want update this element? y/n ?");
        if (toupper(sureToDelete) == 'Y')
        {
            updateRecordFromVector(vClients, ClientAn);
            UpdateFile(vClients);
            cout << "Client updated with Successfully \n";
        }
        else
        {
            cout << "Operation Canceled with success\n";
        }
    }
    else
    {
        cout << "\nclient with Account Number(" << ClientAn << ") "
             << "not found!\n\n";
    }
}

// ---------------------find client functions --------------------------------------------

void findClient(vector<stClient> vClients)
{
    system("cls");
    printSectionTitle("Find Clients Screen ");
    stClient client;

    string ClientAn = input::readString("Enter AccountNumber? ");
    if (checkIfClientAlreadyExist(vClients, ClientAn, client) == enIsClientFound::isFound)
    {
        printRecord(client);
    }
    else
    {
        cout << "\nclient with Account Number(" << ClientAn << ") "
             << "not found!\n\n";
    }
}

// --------------------------------------------------exit Functions------------------------------------------

void exitProgram()
{

    system("cls");
    printSectionTitle("Program Ends :-)");

    exit(0);
}

// ------------------print menu functions -----------------------------------------------

void printMenu()
{

    system("cls");
    cout << setw(70) << "\n======================================================================\n";

    cout << "                          Main Menu Screen                          \n";
    cout << setw(70) << "======================================================================\n";

    cout << "                "
         << "[1] Show Client List.\n";
    cout << "                "
         << "[2] Add new Client.\n";
    cout << "                "
         << "[3] Delete Client.\n";
    cout << "                "
         << "[4] Update Client Info.\n";
    cout << "                "
         << "[5] Find Client.\n";
    cout << "                "
         << "[6] Exit.\n";
    cout << setw(70) << "======================================================================\n";
}
void Wait()
{

    string temp;
    cout << "Press Enter to go back  to  Main Menu...";
    getchar(); 
    cin.ignore();
}
enum enGameChoices
{
    ShowClient = 1,
    AddClient,
    DeleteClient,
    UpdateClient,
    FindClient,
    Exit
};

void ManageUserChoices(enGameChoices GameChoice, vector<stClient> &vClients)
{

    switch (GameChoice)
    {
    case enGameChoices::ShowClient:
        printClients(vClients);
        break;

    case enGameChoices::AddClient:
        AddClients(vClients);
        break;

    case enGameChoices::DeleteClient:
        deleteClient(vClients); // [3]
        break;
    case enGameChoices::UpdateClient:
        Update(vClients); // [4]
        break;

    case enGameChoices::FindClient:
        findClient(vClients); // [5]
        break;

    case enGameChoices::Exit:
        exitProgram(); // [6]
        break;
    }

    Wait();
}

void StartBank()
{
    vector<stClient> vClients = loadClientsToVector();

    int userChoice = 0;
    do
    {
        
            printMenu();
            userChoice = input::readIntegerInRange(enGameChoices::ShowClient, enGameChoices::Exit, "Choose what do you want to do [1 to 6]? ");

            ManageUserChoices(enGameChoices(userChoice), vClients);
        
    

    } while (enGameChoices(userChoice) != enGameChoices::Exit);
}

int main()
{
    try
    {
        StartBank();
    }
    catch (const std::exception &e)
    {
        // Catch the exception and handle it
        system("cls"); 
        std::cerr << "\nCaught exception: " << e.what() << std::endl;
        cin.clear(); 
    }


    return 0;
}