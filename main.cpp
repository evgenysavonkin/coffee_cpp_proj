#include <iostream>
#include <Windows.h>

using namespace std;

double const ESPRESSO_PRICE = 3.0;
double const LATTE_PRICE = 4.0;
int const MAX_NUMBER_OF_ATTEMPTS = 3;
double const CAPPUCCINO_PRICE = 3.5;
int const SERVICE_PIN = 1234;
double const NOMINAL[] = {0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0};
string const MAIN_MENU_ERROR_MSG = "Unknown command! Enter the number in range [1...5]";
string const SERVICE_MENU_ERROR_MSG = "Unknown command! Enter the number in range [1...4]";

double REVENUE = 0.0;
double BALANCE = 0.0;
int CUPS_QUANTITY = 700;
bool IS_SERVICE_MENU = false;
bool IS_MACHINE_LOCKED = false;

void showMenuAndGetInput();

void switchMainMenu(int userInput);

void switchServiceMenu(int userInput);

void showMainMenu();

void showServiceMenu();

void showRevenue();

void takeRevenue();

void showCupsQuantity();

void makeCoffee(double price);

void depositToBalance();

bool checkNominal(double money);

bool removeFromBalance(double money);

void validatePerson();

void showProgress();


int main() {
    cout << "Welcome!" << endl;
    showMenuAndGetInput();
    return 0;
}

void showMenuAndGetInput() {
    int userInput = 0;

    while (true) {
        if (IS_MACHINE_LOCKED) {
            cout << "The machine is blocked!" << endl;
            break;
        }
        if (IS_SERVICE_MENU) {
            showServiceMenu();
            cin >> userInput;
            switchServiceMenu(userInput);
            continue;
        }

        showMainMenu();
        cin >> userInput;
        switchMainMenu(userInput);
    }
}

void switchMainMenu(int userInput) {
    switch (userInput) {
        case 1:
            depositToBalance();
            break;
        case 2:
            makeCoffee(CAPPUCCINO_PRICE);
            break;
        case 3:
            makeCoffee(LATTE_PRICE);
            break;
        case 4:
            makeCoffee(ESPRESSO_PRICE);
            break;
        case 5:
            validatePerson();
            break;
        default:
            cout << endl << MAIN_MENU_ERROR_MSG << endl;
            break;
    }
}

void validatePerson() {
    int currNumberOfAttempts = 0;
    int pinCode = 0;
    cout << endl << "Enter a PIN-code: " << endl;

    while (true) {
        if (currNumberOfAttempts >= 1 && currNumberOfAttempts != MAX_NUMBER_OF_ATTEMPTS) {
            cout << endl << "Enter a PIN-code again: " << endl;
        }
        if (currNumberOfAttempts == MAX_NUMBER_OF_ATTEMPTS) {
            IS_MACHINE_LOCKED = true;
            return;
        }

        cin >> pinCode;

        if (pinCode == SERVICE_PIN) {
            IS_SERVICE_MENU = true;
            break;
        }

        currNumberOfAttempts++;
    }
}

void switchServiceMenu(int userInput) {
    switch (userInput) {
        case 1:
            showRevenue();
            break;
        case 2:
            takeRevenue();
            break;
        case 3:
            showCupsQuantity();
            break;
        case 4:
            IS_SERVICE_MENU = false;
            break;
        default:
            cout << endl << SERVICE_MENU_ERROR_MSG << endl;
            break;
    }
}

void showMainMenu() {
    cout << endl << "Main menu" << endl;
    cout << "Current balance: " << BALANCE << " BYN" << endl;
    cout << "1. Top up the balance" << endl;
    cout << "2. Cappuccino - " << CAPPUCCINO_PRICE << " BYN" << endl;
    cout << "3. Latte - " << LATTE_PRICE << " BYN" << endl;
    cout << "4. Espresso - " << ESPRESSO_PRICE << " BYN" << endl;
    cout << "5. Service" << endl;
}

void showServiceMenu() {
    cout << endl << "Service menu" << endl;
    cout << "1. Check the revenue" << endl;
    cout << "2. Take the revenue" << endl;
    cout << "3. Check the number of cups" << endl;
    cout << "4. Return to the main menu" << endl;
}

void showRevenue() {
    cout << endl << "The revenue is " << REVENUE << " BYN" << endl;
}

void takeRevenue() {
    REVENUE = 0;
}

void showCupsQuantity() {
    cout << endl << "The number of cups is " << CUPS_QUANTITY << endl;
}

void makeCoffee(double price) {
    if (removeFromBalance(price)) {
        if (CUPS_QUANTITY > 0) {
            CUPS_QUANTITY -= 1;

            showProgress();

            cout << endl << "Your flavoured coffee is ready!" << endl;
        } else {
            cout << endl << "Not enough cups!" << endl;
        }
    } else {
        cout << endl << "Not enough money!" << endl;
    }
}

void showProgress() {
    cout << endl << "Your coffee is getting ready.." << endl;

    for (int i = 0; i < 10; ++i) {
        Sleep(500);
        cout << "#";
    }
    cout << " 100%";
}

void depositToBalance() {
    double money = 0.0;

    cout << endl << "Enter the amount of the top-up:" << endl;
    cin >> money;

    if (checkNominal(money)) {
        BALANCE += money;
        REVENUE += money;
        cout << money << " BYN have been credited to the balance" << endl;
    } else {
        cout << "The machine accepts only belarusian coins with the appropriate denomination!" << endl;
    }

}

bool checkNominal(double money) {
    for (int i = 0; i < sizeof(NOMINAL); ++i) {
        if (NOMINAL[i] == money) {
            return true;
        }
    }
    return false;
}

bool removeFromBalance(double money) {
    if (BALANCE >= money) {
        BALANCE -= money;
        return true;
    } else {
        return false;
    }
}


