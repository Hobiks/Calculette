#include <iostream>
#include <stdexcept>

using namespace std;

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        throw invalid_argument("Division by zero is not allowed.");
    }
    return a / b;
}

void displayMenu() {
    cout << "Simple Calculator" << endl;
    cout << "1. Add" << endl;
    cout << "2. Subtract" << endl;
    cout << "3. Multiply" << endl;
    cout << "4. Divide" << endl;
    cout << "5. Exit" << endl;
}

int main() {
    int choice;
    double num1, num2;

    while (true) {
        displayMenu();
        cout << "Choose an operation: ";
        cin >> choice;

        if (choice == 5) {
            cout << "Exiting..." << endl;
            break;
        }

        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter second number: ";
        cin >> num2;

        try {
            switch (choice) {
                case 1:
                    cout << "Result: " << add(num1, num2) << endl;
                    break;
                case 2:
                    cout << "Result: " << subtract(num1, num2) << endl;
                    break;
                case 3:
                    cout << "Result: " << multiply(num1, num2) << endl;
                    break;
                case 4:
                    cout << "Result: " << divide(num1, num2) << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
