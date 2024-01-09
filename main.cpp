#include <iostream>
#include <Windows.h>

using namespace std;

double const ESPRESSO_PRICE = 1.50;
double const LATTE_PRICE = 1.80;
int const MAX_NUMBER_OF_ATTEMPTS = 3;
double const CAPPUCCINO_PRICE = 1.80;
int const SERVICE_PIN = 1234;
int const MAX_NUMBER_OF_CUPS = 700;
double const NOMINAL[] = {10, 20, 50, 1, 2};

double currRevenue = 0.0;
double currBalance = 0.0;
int currCupsQuantity = 1;
bool isServiceMenu = false;
bool isMachineLocked = false;

void showMenuAndGetInput();
void switchMainMenu(int userInput);
void switchServiceMenu(int userInput);
void showMainMenu();
void showServiceMenu();
void takeRevenue();
void makeCoffee(double price);
void depositToBalance();
bool checkNominal(double money);
bool removeFromBalance(double money);
void validatePerson();
void showProgress();
void topUpNumberOfCups();
double convertCoinToDouble(double money);
bool checkAmountOfCups();
bool isCoin(double money);


int main() {
    showMenuAndGetInput();
    return 0;
}

bool checkAmountOfCups(){
    return currCupsQuantity == 0;
}

void showMenuAndGetInput() {
    int userInput = 0;

    while (true) {
        if (checkAmountOfCups()){
            cout << endl << "Not enough cups! You won't get coffee!" << endl;
        }
        if (isMachineLocked) {
            cout << endl << "The PIN-code was entered incorrectly 3 times." << endl << "The machine is blocked!"
                 << endl;
            break;
        }
        if (isServiceMenu) {
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
            break;
    }
}

void validatePerson() {
    int currNumberOfAttempts = 0;
    int pinCode = 0;
    cout << endl << "Enter a PIN-code: " << endl;

    while (true) {
        if (currNumberOfAttempts >= 1 && currNumberOfAttempts != MAX_NUMBER_OF_ATTEMPTS) {
            cout << "Incorrect PIN-code!" << endl;
            cout << endl << "Enter a PIN-code again: " << endl;
        }
        if (currNumberOfAttempts == MAX_NUMBER_OF_ATTEMPTS) {
            cout << "Incorrect PIN-code!" << endl;
            isMachineLocked = true;
            return;
        }

        cin >> pinCode;

        if (pinCode == SERVICE_PIN) {
            isServiceMenu = true;
            break;
        }

        currNumberOfAttempts++;
    }
}

void switchServiceMenu(int userInput) {
    switch (userInput) {
        case 1:
            takeRevenue();
            break;
        case 2:
            topUpNumberOfCups();
            break;
        case 3:
            isServiceMenu = false;
            break;
        default:
            break;
    }
}

void showMainMenu() {
    cout << endl << "Current balance: " << currBalance << " BYN" << endl;
    cout << "1. Insert coin" << endl;
    cout << "2. Cappuccino - " << CAPPUCCINO_PRICE << " BYN" << endl;
    cout << "3. Latte - " << LATTE_PRICE << " BYN" << endl;
    cout << "4. Espresso - " << ESPRESSO_PRICE << " BYN" << endl;
    cout << "5. Service" << endl;
}

void showServiceMenu() {
    cout << endl << "Current revenue: " << currRevenue << " BYN" << endl;
    cout << "Current number of cups: " << currCupsQuantity << endl;
    cout << "1. Withdraw revenue" << endl;
    cout << "2. Replenish the number of cups" << endl;
    cout << "3. Return to the main menu" << endl;
}

void topUpNumberOfCups() {
    int numberOfCups = 0;

    cout << endl << "Enter the number of cups you want to replenish the stock with:" << endl;
    cin >> numberOfCups;

    int sumOfCups = currCupsQuantity + numberOfCups;
    if (sumOfCups > MAX_NUMBER_OF_CUPS) {
        currCupsQuantity = 700;
        return;
    }

    currCupsQuantity += numberOfCups;
}

void takeRevenue() {
    cout << endl << "The revenue was withdrawn. Current revenue: 0 BYN" << endl;
    currRevenue = 0;
}

void makeCoffee(double price) {
    if (removeFromBalance(price)) {
        if (currCupsQuantity > 0) {
            currCupsQuantity -= 1;

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

bool isCoin(double money) {
    if (money == 10 || money == 20 || money == 50) {
        return true;
    }

    return false;
}

double convertCoinToDouble(double money) {
    return money * 0.01;
}

void depositToBalance() {
    double money = 0.0;

    cout << endl << "Enter the amount of the top-up:" << endl;
    cin >> money;

    if (!checkNominal(money)) {
        cout << "The machine accepts only belarusian coins with the appropriate denomination!" << endl;
        return;
    }

    if (isCoin(money)) {
        double currCoin = convertCoinToDouble(money);
        currBalance += currCoin;
        currRevenue += currCoin;
        cout << endl << currCoin << " BYN have been credited to the currBalance" << endl;
        return;
    }

    currBalance += money;
    currRevenue += money;
    cout << endl << money << " BYN have been credited to the currBalance" << endl;
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
    if (currBalance >= money) {
        currBalance -= money;
        return true;
    } else {
        return false;
    }
}


