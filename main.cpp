#include <iostream>
#include <clocale>
#include <Windows.h>

using namespace std;

double const ESPRESSO_PRICE = 3.0;
double const LATTE_PRICE = 4.0;
int const MAX_NUMBER_OF_ATTEMPTS = 3;
double const CAPPUCCINO_PRICE = 3.5;
int const SERVICE_PIN = 1234;
double const NOMINAL[] = {0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0};

double revenue = 0.0;
double balance = 0.0;
int cupsQuantity = 700;
bool isServiceMenu = false;
bool isMachineLocked = false;

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
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    cout << "Добро пожаловать!" << endl;
    showMenuAndGetInput();
    return 0;
}

void showMenuAndGetInput() {
    int userInput = 0;

    while (true) {
        if (isMachineLocked) {
            cout << "Автомат заблокирован!" << endl;
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
            makeCoffee(ESPRESSO_PRICE);
            break;
        case 3:
            makeCoffee(LATTE_PRICE);
            break;
        case 4:
            makeCoffee(CAPPUCCINO_PRICE);
            break;
        case 5:
            validatePerson();
            break;
        default:
            cout << endl << "Неизвестная команда! Введите число в промежутке [1...5]" << endl;
            break;
    }
}

void validatePerson() {
    int currNumberOfAttempts = 0;
    int pinCode = 0;
    cout << endl << "Введите PIN-код: " << endl;

    while (true) {
        if (currNumberOfAttempts >= 1) {
            cout << endl << "Введите PIN-код ещё раз: " << endl;
        }
        if (currNumberOfAttempts == MAX_NUMBER_OF_ATTEMPTS) {
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
            showRevenue();
            break;
        case 2:
            takeRevenue();
            break;
        case 3:
            showCupsQuantity();
            break;
        case 4:
            isServiceMenu = false;
        default:
            cout << endl << "Неизвестная команда! Введите число в промежутке [1...4]" << endl;
            break;
    }
}

void showMainMenu() {
    cout << endl << "Главное меню" << endl;
    cout << "Текущий баланс: " << balance << " BYN" << endl;
    cout << "1. Пополнить баланс" << endl;
    cout << "2. Эспрессо - " << ESPRESSO_PRICE << " BYN" << endl;
    cout << "3. Латте - " << LATTE_PRICE << " BYN" << endl;
    cout << "4. Капучино - " << CAPPUCCINO_PRICE << " BYN" << endl;
    cout << "5. Сервисное меню" << endl;
}

void showServiceMenu() {
    cout << endl << "Сервисное меню" << endl;
    cout << "1. Просмотреть выручку" << endl;
    cout << "2. Изъять выручку" << endl;
    cout << "3. Просмотреть количество стаканов" << endl;
    cout << "4. Вернуться в основное меню" << endl;
}

void showRevenue() {
    cout << endl << "Выручка составляет " << revenue << " BYN" << endl;
}

void takeRevenue() {
    revenue = 0;
}

void showCupsQuantity() {
    cout << endl << "Количество стаканчиков составляет " << cupsQuantity << endl;
}

void makeCoffee(double price) {
    if (removeFromBalance(price)) {
        if (cupsQuantity > 0) {
            cupsQuantity -= 1;

            showProgress();

            cout << endl << "Ваш ароматный кофе готов!" << endl;
        } else {
            cout << endl << "Недостаточно стаканов!" << endl;
        }
    } else {
        cout << endl << "Недостаточно средств!" << endl;
    }
}

void showProgress() {
    cout << endl << "Ваш кофе готовится!" << endl;

    for (int i = 0; i < 10; ++i) {
        Sleep(500);
        cout << "#";
    }
    cout << " 100%";
}

void depositToBalance() {
    double money = 0.0;

    cout << endl << "Введите сумму пополнения:" << endl;
    cin >> money;

    if (checkNominal(money)) {
        balance += money;
        revenue += money;
        cout << "Ваши " << money << " BYN зачислены на баланс" << endl;
    } else {
        cout << "Автомат принимает только белорусские монеты с соответствующим номиналом!" << endl;
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
    if (balance >= money) {
        balance -= money;
        return true;
    } else {
        return false;
    }
}


