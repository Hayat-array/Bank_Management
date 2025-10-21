// #include <iostream>
// #include <vector>
// #include <string>
// #include <limits>
// #include <iomanip>
// #include <fstream>
// #include <sstream>
// #include <cstdlib>
// #include <algorithm>
// #include <map>
// #include <ctime>
// using namespace std;

// // Color codes for styling (works on Windows 10+ and most Unix-like systems)
// const string RESET = "\033[0m";
// const string BOLD = "\033[1m";
// const string RED = "\033[31m";
// const string GREEN = "\033[32m";
// const string YELLOW = "\033[33m";
// const string BLUE = "\033[34m";
// const string MAGENTA = "\033[35m";
// const string CYAN = "\033[36m";
// const string WHITE = "\033[37m";
// const string BG_BLACK = "\033[40m";
// const string BG_BLUE = "\033[44m";

// // Function to display styled headers with borders
// void printHeader(const string& title, const string& color = BLUE) {
//     cout << BG_BLUE << BOLD << WHITE;
//     cout << "\n" << string(70, '═');
//     cout << "\n  " << title << "  ";
//     cout << "\n" << string(70, '═');
//     cout << RESET << endl;
// }

// // Function to display styled menu options
// void printMenuOption(int number, const string& text, const string& color = WHITE) {
//     cout << "  " << BOLD << number << ". " << RESET << color << text << RESET << endl;
// }

// // Function to display styled messages
// void printMessage(const string& message, const string& color = GREEN) {
//     cout << color << "  " << message << RESET << endl;
// }

// // Function to display styled errors
// void printError(const string& error) {
//     cout << RED << "  ❌ " << error << RESET << endl;
// }

// // Function to display styled success messages
// void printSuccess(const string& success) {
//     cout << GREEN << "  ✅ " << success << RESET << endl;
// }

// // Function to clear input buffer
// void clearInputBuffer() {
//     cin.clear();
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
// }

// // Function to get secure input (basic implementation)
// string getSecureInput(const string& prompt) {
//     cout << prompt;
//     string input;
//     getline(cin, input);
//     return input;
// }

// // Function to display a separator line
// void printSeparator() {
//     cout << BG_BLUE << string(70, '─') << RESET << endl;
// }

// struct BankAccount {
//     string name;
//     long long accountNumber;
//     double balance;
//     string password;
//     string recoveryPhrase;
//     vector<string> transactions;
    
//     string toString() const {
//         ostringstream oss;
//         oss << name << "," << accountNumber << "," << fixed << setprecision(2) << balance << "," 
//             << password << "," << recoveryPhrase;
//         return oss.str();
//     }
    
//     static BankAccount fromString(const string& line) {
//         stringstream ss(line);
//         string name, accStr, balStr, pwd, recovery;
        
//         if (!getline(ss, name, ',') || 
//             !getline(ss, accStr, ',') || 
//             !getline(ss, balStr, ',') || 
//             !getline(ss, pwd, ',') || 
//             !getline(ss, recovery)) {
//             throw runtime_error("Invalid account data format");
//         }
        
//         BankAccount acc;
//         acc.name = name;
//         try {
//             acc.accountNumber = stoll(accStr);
//             acc.balance = stod(balStr);
//         } catch (const exception& e) {
//             throw runtime_error("Invalid numeric data in account");
//         }
//         acc.password = pwd;
//         acc.recoveryPhrase = recovery;
//         acc.loadTransactions();
//         return acc;
//     }
    
//     void recordTransaction(const string& action, double amount) {
//         ostringstream t;
//         t << action << " $" << fixed << setprecision(2) << amount << " | Balance: $" << balance;
//         transactions.push_back(t.str());
//         saveTransactionToFile(t.str());
//     }
    
//     void showTransactions() const {
//         printHeader("Transaction History for " + name, CYAN);
//         if (transactions.empty()) {
//             printMessage("No transactions found.", YELLOW);
//         } else {
//             for (const string& t : transactions) {
//                 cout << "  " << t << endl;
//             }
//         }
//     }
    
//     void saveTransactionToFile(const string& entry) const {
//         ofstream file("txn_" + to_string(accountNumber) + ".txt", ios::app);
//         if (file.is_open()) {
//             file << entry << "\n";
//             file.close();
//         }
//     }
    
//     void loadTransactions() {
//         transactions.clear();
//         ifstream file("txn_" + to_string(accountNumber) + ".txt");
//         string line;
//         while (getline(file, line)) {
//             if (!line.empty()) {
//                 transactions.push_back(line);
//             }
//         }
//         file.close();
//     }
// };

// vector<BankAccount> accounts;
// const string FILE_NAME = "accounts.txt";
// const string ADMIN_FILE = "admins.txt";
// map<string, pair<string, string>> admins;

// bool isUniqueAccountNumber(long long accNo) {
//     for (const auto& acc : accounts) {
//         if (acc.accountNumber == accNo) return false;
//     }
//     return true;
// }

// long long generateUniqueAccountNumber() {
//     static bool seeded = false;
//     if (!seeded) {
//         srand(static_cast<unsigned int>(time(0)));
//         seeded = true;
//     }
    
//     long long num;
//     int attempts = 0;
//     do {
//         num = 100000000000LL + (static_cast<long long>(rand()) * rand()) % 900000000000LL;
//         attempts++;
//         if (attempts > 1000) {
//             throw runtime_error("Unable to generate unique account number");
//         }
//     } while (!isUniqueAccountNumber(num));
//     return num;
// }

// void saveAccounts() {
//     ofstream file(FILE_NAME);
//     if (!file.is_open()) {
//         printError("Unable to save accounts to file");
//         return;
//     }
    
//     for (const auto& a : accounts) {
//         file << a.toString() << "\n";
//     }
//     file.close();
// }

// void loadAccounts() {
//     accounts.clear();
//     ifstream file(FILE_NAME);
//     if (!file.is_open()) {
//         return; // File doesn't exist yet, which is fine
//     }
    
//     string line;
//     while (getline(file, line)) {
//         if (!line.empty()) {
//             try {
//                 accounts.push_back(BankAccount::fromString(line));
//             } catch (const exception& e) {
//                 printError("Error loading account: " + string(e.what()));
//             }
//         }
//     }
//     file.close();
// }

// void loadAdmins() {
//     admins.clear();
//     ifstream file(ADMIN_FILE);
//     if (!file.is_open()) {
//         return; // File doesn't exist yet, which is fine
//     }
    
//     string line;
//     while (getline(file, line)) {
//         stringstream ss(line);
//         string uname, pwd, recovery;
//         if (getline(ss, uname, ',') && 
//             getline(ss, pwd, ',') && 
//             getline(ss, recovery) && 
//             !uname.empty()) {
//             admins[uname] = {pwd, recovery};
//         }
//     }
//     file.close();
// }

// void saveAdmins() {
//     ofstream file(ADMIN_FILE);
//     if (!file.is_open()) {
//         printError("Unable to save admin data");
//         return;
//     }
    
//     for (const auto& admin : admins) {
//         file << admin.first << "," << admin.second.first << "," << admin.second.second << "\n";
//     }
//     file.close();
// }

// void createAdmin() {
//     string uname, pwd, recovery;
//     printHeader("Create New Admin");
    
//     cout << "Enter new admin username: ";
//     cin >> uname;
    
//     if (admins.find(uname) != admins.end()) {
//         printError("Admin username already exists!");
//         return;
//     }
    
//     cout << "Set admin password: ";
//     cin >> pwd;
//     cout << "Set recovery phrase: ";
//     clearInputBuffer();
//     getline(cin, recovery);
    
//     admins[uname] = {pwd, recovery};
//     saveAdmins();
//     printSuccess("Admin created successfully!");
// }

// void forgotAdminPassword() {
//     string uname, recovery;
//     printHeader("Forgot Admin Password");
    
//     cout << "Enter admin username: ";
//     cin >> uname;
    
//     if (admins.find(uname) == admins.end()) {
//         printError("Admin not found.");
//         return;
//     }
    
//     cout << "Enter recovery phrase: ";
//     clearInputBuffer();
//     getline(cin, recovery);
    
//     if (admins[uname].second == recovery) {
//         string newPwd;
//         cout << "Enter new password: ";
//         getline(cin, newPwd);
//         admins[uname].first = newPwd;
//         saveAdmins();
//         printSuccess("Password updated successfully.");
//     } else {
//         printError("Recovery phrase incorrect.");
//     }
// }

// void forgotUserPassword() {
//     long long accNo;
//     string recovery;
//     printHeader("Forgot User Password");
    
//     cout << "Enter account number: ";
//     if (!(cin >> accNo)) {
//         printError("Invalid account number format.");
//         clearInputBuffer();
//         return;
//     }
    
//     clearInputBuffer();
//     cout << "Enter recovery phrase: ";
//     getline(cin, recovery);
    
//     for (auto& acc : accounts) {
//         if (acc.accountNumber == accNo && acc.recoveryPhrase == recovery) {
//             cout << "Enter new password: ";
//             getline(cin, acc.password);
//             saveAccounts();
//             printSuccess("Password updated successfully.");
//             return;
//         }
//     }
//     printError("Invalid account number or recovery phrase.");
// }

// void deleteAccount() {
//     long long accNo;
//     printHeader("Delete Account");
    
//     cout << "Enter account number to delete: ";
//     if (!(cin >> accNo)) {
//         printError("Invalid account number format.");
//         clearInputBuffer();
//         return;
//     }
    
//     auto it = find_if(accounts.begin(), accounts.end(), [&](const BankAccount& acc) {
//         return acc.accountNumber == accNo;
//     });
    
//     if (it != accounts.end()) {
//         accounts.erase(it);
//         saveAccounts();
//         printSuccess("Account deleted successfully.");
//     } else {
//         printError("Account not found.");
//     }
// }

// void viewAllAccounts() {
//     printHeader("All Bank Accounts", MAGENTA);
    
//     if (accounts.empty()) {
//         printMessage("No accounts found.", YELLOW);
//         return;
//     }
    
//     for (const auto& acc : accounts) {
//         cout << "  " << BOLD << acc.name << RESET << " | Account: " << acc.accountNumber 
//              << " | Balance: $" << fixed << setprecision(2) << GREEN << acc.balance << RESET << endl;
//     }
// }

// void updateAccountName() {
//     long long accNo;
//     printHeader("Update Account Name");
    
//     cout << "Enter account number to update name: ";
//     if (!(cin >> accNo)) {
//         printError("Invalid account number format.");
//         clearInputBuffer();
//         return;
//     }
    
//     for (auto& acc : accounts) {
//         if (acc.accountNumber == accNo) {
//             cout << "Enter new name: ";
//             clearInputBuffer();
//             getline(cin, acc.name);
//             saveAccounts();
//             printSuccess("Name updated successfully.");
//             return;
//         }
//     }
//     printError("Account not found.");
// }

// void generateTransactionCSV() {
//     printHeader("Export Transaction History", YELLOW);
    
//     ofstream csvFile("all_transactions.csv");
//     if (!csvFile.is_open()) {
//         printError("Error creating CSV file!");
//         return;
//     }
    
//     csvFile << "Account Number,Name,Transaction Details\n";
//     for (auto& acc : accounts) {
//         acc.loadTransactions();
//         for (const string& t : acc.transactions) {
//             csvFile << acc.accountNumber << "," << acc.name << ",\"" << t << "\"\n";
//         }
//     }
    
//     csvFile.close();
//     printSuccess("Transaction history downloaded to 'all_transactions.csv'");
// }

// void adminLogin() {
//     string uname, pwd;
//     printHeader("Admin Login");
    
//     cout << "Enter admin username: ";
//     cin >> uname;
//     cout << "Enter admin password: ";
//     cin >> pwd;
//     if (admins.find(uname) != admins.end() && admins[uname].first == pwd) {
//         printSuccess("Admin login successful!");
        
//         while (true) {
//             printHeader("Admin Panel", MAGENTA);
//             printMenuOption(1, "View All Accounts");
//             printMenuOption(2, "Update Account Name");
//             printMenuOption(3, "Delete Account");
//             printMenuOption(4, "Download Transaction History (CSV)");
//             printMenuOption(5, "Logout");
            
//             cout << "Enter your choice: ";
//             int ch;
//             if (!(cin >> ch)) {
//                 printError("Invalid input. Please enter a number.");
//                 clearInputBuffer();
//                 continue;
//             }
            
//             switch (ch) {
//                 case 1: viewAllAccounts(); break;
//                 case 2: updateAccountName(); break;
//                 case 3: deleteAccount(); break;
//                 case 4: generateTransactionCSV(); break;
//                 case 5: 
//                     printMessage("Logging out...", YELLOW);
//                     return;
//                 default:
//                     printError("Invalid choice. Please try again.");
//             }
//         }
//     } else {
//         printError("Invalid admin credentials.");
//     }
// }

// void createAccount() {
//     string name, password, recovery;
//     printHeader("Create New Account");
    
//     cout << "Enter your full name: ";
//     clearInputBuffer();
//     getline(cin, name);
    
//     if (name.empty()) {
//         printError("Name cannot be empty.");
//         return;
//     }
    
//     cout << "Set your password: ";
//     getline(cin, password);
    
//     if (password.empty()) {
//         printError("Password cannot be empty.");
//         return;
//     }
    
//     cout << "Set recovery phrase: ";
//     getline(cin, recovery);
    
//     if (recovery.empty()) {
//         printError("Recovery phrase cannot be empty.");
//         return;
//     }
    
//     try {
//         long long accNo = generateUniqueAccountNumber();
//         BankAccount newAcc;
//         newAcc.name = name;
//         newAcc.accountNumber = accNo;
//         newAcc.balance = 0.0;
//         newAcc.password = password;
//         newAcc.recoveryPhrase = recovery;
        
//         accounts.push_back(newAcc);
//         saveAccounts();
        
//         printSuccess("Account created successfully!");
//         cout << "Your account number is: " << BOLD << accNo << RESET << endl;
//         cout << "Please save this number for future logins.\n";
//     } catch (const exception& e) {
//         printError("Error creating account: " + string(e.what()));
//     }
// }

// BankAccount* findAccount(long long accNo) {
//     for (auto& acc : accounts) {
//         if (acc.accountNumber == accNo) {
//             return &acc;
//         }
//     }
//     return nullptr;
// }

// void deposit(BankAccount* acc) {
//     double amount;
//     printHeader("Deposit Money");
    
//     cout << "Enter deposit amount: $";
//     if (!(cin >> amount)) {
//         printError("Invalid amount format.");
//         clearInputBuffer();
//         return;
//     }
    
//     if (amount <= 0) {
//         printError("Invalid amount. Please enter a positive value.");
//         return;
//     }
    
//     acc->balance += amount;
//     acc->recordTransaction("Deposit", amount);
//     saveAccounts();
    
//     cout << GREEN << "✅ Deposit successful. New balance: $" << fixed << setprecision(2) << acc->balance << RESET << endl;
// }

// void withdraw(BankAccount* acc) {
//     double amount;
//     printHeader("Withdraw Money");
    
//     cout << "Enter withdrawal amount: $";
//     if (!(cin >> amount)) {
//         printError("Invalid amount format.");
//         clearInputBuffer();
//         return;
//     }
    
//     if (amount <= 0) {
//         printError("Invalid amount. Please enter a positive value.");
//         return;
//     }
    
//     if (amount > acc->balance) {
//         printError("Insufficient funds. Current balance: $" + to_string(acc->balance));
//         return;
//     }
    
//     acc->balance -= amount;
//     acc->recordTransaction("Withdrawal", amount);
//     saveAccounts();
    
//     cout << GREEN << "✅ Withdrawal successful. New balance: $" << fixed << setprecision(2) << acc->balance << RESET << endl;
// }

// void viewBalance(const BankAccount* acc) {
//     printHeader("Account Balance", YELLOW);
//     cout << "Current balance: $" << GREEN << fixed << setprecision(2) << acc->balance << RESET << endl;
// }

// void userLogin() {
//     long long accNo;
//     string password;
//     printHeader("User Login");
    
//     cout << "Enter account number: ";
//     if (!(cin >> accNo)) {
//         printError("Invalid account number format.");
//         clearInputBuffer();
//         return;
//     }
    
//     cout << "Enter password: ";
//     cin >> password;
    
//     BankAccount* acc = findAccount(accNo);
//     if (acc && acc->password == password) {
//         printSuccess("Login successful! Welcome, " + acc->name + "!");
        
//         while (true) {
//             printHeader("User Menu", CYAN);
//             printMenuOption(1, "Deposit Money");
//             printMenuOption(2, "Withdraw Money");
//             printMenuOption(3, "View Balance");
//             printMenuOption(4, "View Transactions");
//             printMenuOption(5, "Logout");
            
//             cout << "Enter your choice: ";
//             int choice;
//             if (!(cin >> choice)) {
//                 printError("Invalid input. Please enter a number.");
//                 clearInputBuffer();
//                 continue;
//             }
            
//             switch (choice) {
//                 case 1: deposit(acc); break;
//                 case 2: withdraw(acc); break;
//                 case 3: viewBalance(acc); break;
//                 case 4: acc->showTransactions(); break;
//                 case 5: 
//                     printMessage("Logging out...", YELLOW);
//                     return;
//                 default:
//                     printError("Invalid choice. Please try again.");
//             }
//         }
//     } else {
//         printError("Invalid account number or password.");
//     }
// }

// int main() {
//     loadAccounts();
//     loadAdmins();
    
//     while (true) {
//         printHeader("Bank Management System", BLUE);
//         printMenuOption(1, "Admin Login");
//         printMenuOption(2, "Create New Account");
//         printMenuOption(3, "User Login");
//         printMenuOption(4, "Create Admin");
//         printMenuOption(5, "Forgot Admin Password");
//         printMenuOption(6, "Forgot User Password");
//         printMenuOption(7, "Exit");
        
//         cout << "Enter your choice: ";
//         int choice;
//         if (!(cin >> choice)) {
//             printError("Invalid input. Please enter a number.");
//             clearInputBuffer();
//             continue;
//         }
        
//         switch (choice) {
//             case 1: adminLogin(); break;
//             case 2: createAccount(); break;
//             case 3: userLogin(); break;
//             case 4: createAdmin(); break;
//             case 5: forgotAdminPassword(); break;
//             case 6: forgotUserPassword(); break;
//             case 7:
//                 printMessage("Thank you for using Bank Management System!", YELLOW);
//                 return 0;
//             default:
//                 printError("Invalid choice.");
//         }
//     }
// }

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <chrono>
#include <thread>
using namespace std;

// Color codes for styling
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string BG_BLUE = "\033[44m";
const string BG_MAGENTA = "\033[45m";

void printHeader(const string& title, const string& color = BLUE) {
    cout << BG_BLUE << BOLD << WHITE;
    cout << "\n" << BG_MAGENTA << "╔══════════════════════════════════════════════════════════════╗" << RESET << endl;
    cout << BG_BLUE << "║" << RESET << "  " << BOLD << color << title << RESET << BG_BLUE << "  ║" << RESET << endl;
    cout << BG_BLUE << "╚══════════════════════════════════════════════════════════════╝" << RESET << endl;
}

void printMenuOption(int number, const string& text, const string& color = WHITE) {
    cout << BOLD << number << ". " << RESET << color << text << RESET << endl;
}

void printError(const string& error) {
    cout << RED << "Error: " << error << RESET << endl;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

struct BankAccount {
    string name;
    long long accountNumber;
    double balance;
    string password;
    string recoveryPhrase;
    vector<string> transactions;

    string toString() const {
        ostringstream oss;
        oss << name << "," << accountNumber << "," << balance << "," << password << "," << recoveryPhrase;
        return oss.str();
    }

    static BankAccount fromString(const string& line) {
        stringstream ss(line);
        string name, accStr, balStr, pass, rec;
        getline(ss, name, ',');
        getline(ss, accStr, ',');
        getline(ss, balStr, ',');
        getline(ss, pass, ',');
        getline(ss, rec);

        BankAccount acc;
        acc.name = name;
        acc.accountNumber = stoll(accStr);
        acc.balance = stod(balStr);
        acc.password = pass;
        acc.recoveryPhrase = rec;
        return acc;
    }
};

map<string, pair<string, string>> admins;
vector<BankAccount> accounts;

bool isUniqueAccountNumber(long long num) {
    for (const auto& acc : accounts) {
        if (acc.accountNumber == num) return false;
    }
    return true;
}

long long generateUniqueAccountNumber() {
    srand(time(0));
    long long num;
    do {
        num = 100000000000 + rand() % 900000000000;
    } while (!isUniqueAccountNumber(num));
    return num;
}

void saveAccounts() {
    ofstream file("accounts.txt");
    for (const auto& acc : accounts) {
        file << acc.toString() << endl;
    }
}

void loadAccounts() {
    accounts.clear();
    ifstream file("accounts.txt");
    string line;
    while (getline(file, line)) {
        accounts.push_back(BankAccount::fromString(line));
    }
}

void saveAdmins() {
    ofstream file("admins.txt");
    for (const auto& admin : admins) {
        file << admin.first << "," << admin.second.first << "," << admin.second.second << endl;
    }
}

void loadAdmins() {
    admins.clear();
    ifstream file("admins.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, pass, rec;
        getline(ss, name, ',');
        getline(ss, pass, ',');
        getline(ss, rec);
        admins[name] = {pass, rec};
    }
}

BankAccount* findAccount(long long num) {
    for (auto& acc : accounts) {
        if (acc.accountNumber == num) return &acc;
    }
    return nullptr;
}

void createAccount() {
    BankAccount acc;
    cout << "Enter name: ";
    clearInputBuffer();
    getline(cin, acc.name);
    acc.accountNumber = generateUniqueAccountNumber();
    cout << "Set password: ";
    getline(cin, acc.password);
    cout << "Set recovery phrase: ";
    getline(cin, acc.recoveryPhrase);
    acc.balance = 0;
    accounts.push_back(acc);
    saveAccounts();
    cout << "Account created. Account Number: " << acc.accountNumber << endl;
}

void userLogin() {
    long long accNo;
    string pass;
    cout << "Enter account number: ";
    cin >> accNo;
    cout << "Enter password: ";
    cin >> pass;

    BankAccount* acc = findAccount(accNo);
    if (acc && acc->password == pass) {
        int ch;
        do {
            cout << "\n1. Deposit\n2. Withdraw\n3. View Balance\n4. Logout\nEnter choice: ";
            cin >> ch;
            switch (ch) {
                case 1: {
                    double amt;
                    cout << "Enter amount to deposit: ";
                    cin >> amt;
                    acc->balance += amt;
                    saveAccounts();
                    break;
                }
                case 2: {
                    double amt;
                    cout << "Enter amount to withdraw: ";
                    cin >> amt;
                    if (amt <= acc->balance) {
                        acc->balance -= amt;
                        saveAccounts();
                    } else {
                        cout << "Insufficient balance.\n";
                    }
                    break;
                }
                case 3:
                    cout << "Balance: $" << acc->balance << endl;
                    break;
            }
        } while (ch != 4);
    } else {
        printError("Invalid login");
    }
}

void createAdmin() {
    string name, pass, rec;
    cout << "Enter new admin username: ";
    cin >> name;
    if (admins.find(name) != admins.end()) {
        printError("Admin already exists");
        return;
    }
    cout << "Enter password: ";
    cin >> pass;
    cout << "Set recovery phrase: ";
    clearInputBuffer();
    getline(cin, rec);
    admins[name] = {pass, rec};
    saveAdmins();
    cout << "Admin created.\n";
}

void adminLogin() {
    string name, pass;
    cout << "Enter admin username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;

    if (admins.find(name) != admins.end() && admins[name].first == pass) {
        int ch;
        do {
            cout << "\n1. View Accounts\n2. Delete Account\n3. Logout\nEnter choice: ";
            cin >> ch;
            switch (ch) {
                case 1:
                    for (auto& acc : accounts)
                        cout << acc.name << " - " << acc.accountNumber << " - $" << acc.balance << endl;
                    break;
                case 2: {
                    long long no;
                    cout << "Enter account number to delete: ";
                    cin >> no;
                    accounts.erase(remove_if(accounts.begin(), accounts.end(), [&](BankAccount& a) {
                        return a.accountNumber == no;
                    }), accounts.end());
                    saveAccounts();
                    break;
                }
            }
        } while (ch != 3);
    } else {
        printError("Invalid admin credentials");
    }
}
void createAdmin1() {
    string name, pass, rec;
    cout << "Enter new admin username: ";
    cin >> name;
    if (admins.find(name) != admins.end()) {
        printError("Admin already exists");
        return;
    }
    cout << "Enter password: ";
    cin >> pass;
    cout << "Set recovery phrase: ";
    clearInputBuffer();
    getline(cin, rec);
    admins[name] = {pass, rec};
    saveAdmins();
    cout << "Admin created.\n";
}


void forgotAdminPassword() {
    string name, rec;
    cout << "Enter admin username: ";
    cin >> name;
    cout << "Enter recovery phrase: ";
    clearInputBuffer();
    getline(cin, rec);

    if (admins.find(name) != admins.end() && admins[name].second == rec) {
        string newPass;
        cout << "Enter new password: ";
        getline(cin, newPass);
        admins[name].first = newPass;
        saveAdmins();
        cout << "Password reset successful.\n";
    } else {
        printError("Invalid recovery");
    }
}

void forgotUserPassword() {
    long long accNo;
    string rec;
    cout << "Enter account number: ";
    cin >> accNo;
    clearInputBuffer();
    cout << "Enter recovery phrase: ";
    getline(cin, rec);

    for (auto& acc : accounts) {
        if (acc.accountNumber == accNo && acc.recoveryPhrase == rec) {
            string newPass;
            cout << "Enter new password: ";
            getline(cin, newPass);
            acc.password = newPass;
            saveAccounts();
            cout << "Password reset successful.\n";
            return;
        }
    }
    printError("Recovery failed");
}

int main() {
    loadAccounts();
    loadAdmins();
    while (true) {
        printHeader("Bank Management System");
        printMenuOption(1, "Admin Login");
        printMenuOption(2, "Create New Account");
        printMenuOption(3, "User Login");
        printMenuOption(4, "Create Admin");
        printMenuOption(5, "Forgot Admin Password");
        printMenuOption(6, "Forgot User Password");
        printMenuOption(7, "Exit");

        int ch;
        cout << "Enter choice: ";
        cin >> ch;
        switch (ch) {
            case 1: adminLogin(); break;
            case 2: createAccount(); break;
            case 3: userLogin(); break;
            case 4: createAdmin(); break;
            case 5: forgotAdminPassword(); break;
            case 6: forgotUserPassword(); break;
            case 7: return 0;
            default: printError("Invalid option");
        }
    }
}
