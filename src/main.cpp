#include <iostream>
#include <string>
#include <windows.h>
#include "PluginManager.h"
#include "Calculator.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Calculator calc;
    PluginManager manager(calc); 
    manager.scanPlugins("./plugins");
    std::string input;
    std::cout << "\nВведите выражение (или 'exit'):\n> ";
    while (std::getline(std::cin, input) && input != "exit") {
        if (input.empty()) continue;
        try {
            std::string processedExpr = manager.evaluateExpression(input);
            double finalResult = calc.calculate(processedExpr);
            std::cout << "Результат: " << finalResult << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка вычисления: " << e.what() << "\n";
        }
        std::cout << "\n> ";
    }
    return 0;
}