#include <iostream>
#include "LinearRegression.h"

void showMenu() {
    std::cout << "\n--- Linear Regression Program ---\n";
    std::cout << "1. Add Data Point\n";
    std::cout << "2. Fit Model\n";
    std::cout << "3. Predict Value\n";
    std::cout << "4. Display Equation\n";
    std::cout << "5. Clear Data\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    LinearRegression lr;
    int choice;
    double x, y;

    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter x value: ";
                std::cin >> x;
                std::cout << "Enter y value: ";
                std::cin >> y;
                lr.addDataPoint(x, y);
                std::cout << "Data point added.\n";
                break;

            case 2:
                lr.fit();
                std::cout << "Model fitted.\n";
                break;

            case 3:
                std::cout << "Enter x value for prediction: ";
                std::cin >> x;
                std::cout << "Predicted y value: " << lr.predict(x) << std::endl;
                break;

            case 4:
                lr.displayEquation();
                break;

            case 5:
                lr.clearData();
                std::cout << "Data cleared.\n";
                break;

            case 6:
                std::cout << "Exiting program. Goodbye!\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
