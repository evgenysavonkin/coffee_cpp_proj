#include <iostream>
#include <clocale>
#include <Windows.h>

using namespace std;

double const ESPRESSO_PRICE = 3.0;
double const LATTE_PRICE = 4.0;
double const CAPPUCCINO_PRICE = 3.5;

double revenue = 0.0;
double balance = 0.0;
int cup = 700;
//int attempts = 3;


void showMainMenu();

void showServiceMenu();

void useServiceMenu();

void makeCoffee(double price);

void depositToBalance();

bool removeFromBalance(double money);

int main() {
    int input = 0;

    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Добро пожаловать!" << endl;

    while (true) {

        showMainMenu();

        cin >> input;

        if (input == 1) {
            depositToBalance();
        } else if (input == 2) {
            makeCoffee(ESPRESSO_PRICE);
        } else if (input == 3) {
            makeCoffee(LATTE_PRICE);
        } else if (input == 4) {
            makeCoffee(CAPPUCCINO_PRICE);
        } else if (input == 5) {
            // TODO пункты меню, ввод пин-кода
            useServiceMenu();
        } else if (input == 0) {
            // Нужен ли выход?
            break;
        } else {
            cout << "Неизвестная команда" << endl;
        }
    }

    return 0;
}

void showMainMenu() {
    cout << endl << "Текущий баланс: " << balance << " BYN" << endl;
    cout << "1. Пополнить баланс" << endl;
    cout << "2. Эспрессо - " << ESPRESSO_PRICE << "BYN" << endl;
    cout << "3. Латте - " << LATTE_PRICE << "BYN" << endl;
    cout << "4. Капучино - " << CAPPUCCINO_PRICE << "BYN" << endl;
    cout << "5. Сервисное меню" << endl;
}

void showServiceMenu() {
    cout << endl << "1. Просмотреть выручку" << endl;
    cout << "2. Просмотреть количество стаканов" << endl;
    cout << "3. Изъять выручку" << endl;
    cout << "0. Вернуться" << endl;
}

void useServiceMenu() {
    // TODO
    int input = 0;

    while (true) {

        showServiceMenu();

        cin >> input;

        if (input == 1) {
            cout << "Выручка" << endl;
        } else if (input == 2) {
            cout << "Стаканы" << endl;
        } else if (input == 3) {
            cout << "Изъятие" << endl;
        } else if (input == 0) {
            break;
        } else {
            cout << "Неизвестная команда" << endl;
        }
    }
}

void makeCoffee(double price) {
    // TODO Прогресс приготовления
    if (removeFromBalance(price)) {
        if (cup > 0) {
            cup -= 1;
            cout << "Ваш ароматный кофе готов!" << endl;
        } else {
            cout << "Недостаточно стаканов!" << endl;
        }
    } else {
        cout << "Недостаточно средств!" << endl;
    }
}

void depositToBalance() {
    double money = 0.0;

    cout << "Введите сумму пополнения:" << endl;
    cin >> money;

    balance += money;
    revenue += money;
}

bool removeFromBalance(double money) {
    if (balance >= money) {
        balance -= money;
        return true;
    } else {
        return false;
    }
}
