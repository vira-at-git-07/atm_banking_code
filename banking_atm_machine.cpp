#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

string username[100];
string password[100];
int balance[100];

int userCount = 0;
int currentUser = -1;

void signup();
bool login();
void banking();
void quit();
void loadbalance();
void savebalance();

int main() {
    string ans;

    do {
        cout << "\n------------- welcome to vira banks -------------" << endl;
        cout << "1. login" << endl;
        cout << "2. signup" << endl;
        cout << "3. exit" << endl;

        int ch;
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (ch) {
            case 1:
                if (login()) {
                    loadbalance();
                    banking();
                }
                break;

            case 2:
                signup();
                break;

            case 3:
                quit();
                return 0;

            default:
                cout << "invalid choice" << endl;
        }

        cout << "do you want to continue? (yes/no): ";
        cin >> ans;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (ans == "yes");

    cout << "thank you for using vira banks" << endl;
    return 0;
}

void signup() {
    if (userCount >= 100) {
        cout << "user limit reached" << endl;
        return;
    }

    cout << "enter username" << endl;
    getline(cin, username[userCount]);

    cout << "enter password" << endl;
    cin >> password[userCount];
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    balance[userCount] = 0;
    userCount++;

    cout << "signup successful" << endl;
}

bool login() {
    string user, pass;

    cout << "enter username" << endl;
    getline(cin, user);

    cout << "enter password" << endl;
    cin >> pass;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < userCount; i++) {
        if (username[i] == user && password[i] == pass) {
            cout << "login successful" << endl;
            currentUser = i;
            return true;
        }
    }

    cout << "login failed" << endl;
    return false;
}

void banking() {
    int choice;

    do {
        cout << "\nwelcome " << username[currentUser] << endl;
        cout << "1. check balance" << endl;
        cout << "2. deposit" << endl;
        cout << "3. withdraw" << endl;
        cout << "4. logout" << endl;

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "your balance is: " << balance[currentUser] << endl;
                break;

            case 2: {
                int amount;
                cout << "enter amount to deposit: ";
                cin >> amount;

                if (amount > 0) {
                    balance[currentUser] += amount;
                    cout << "deposit successful" << endl;
                } else {
                    cout << "invalid amount" << endl;
                }
                break;
            }

            case 3: {
                int amount;
                cout << "enter amount to withdraw: ";
                cin >> amount;

                if (amount <= 0 || amount > balance[currentUser]) {
                    cout << "invalid withdrawal" << endl;
                } else {
                    balance[currentUser] -= amount;
                    cout << "withdrawal successful" << endl;
                }
                break;
            }

            case 4:
                savebalance();
                cout << "logging out..." << endl;
                currentUser = -1;
                break;

            default:
                cout << "invalid choice" << endl;
        }

    } while (choice != 4);
}

void loadbalance() {
    ifstream in(username[currentUser] + ".txt");
    if (in) {
        in >> balance[currentUser];
    } else {
        balance[currentUser] = 0;
    }
    in.close();
}

void savebalance() {
    ofstream out(username[currentUser] + ".txt");
    out << balance[currentUser];
    out.close();
}

void quit() {
    cout << "thank you for using vira banks" << endl;
}
