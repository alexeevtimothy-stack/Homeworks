#include "PluginManager.h"
#include "Calculator.h"
#include <iostream>
#include <stdexcept>
#include <regex>

namespace fs = std::filesystem;
PluginManager::PluginManager(Calculator& calc) : calcRef(calc) {}
void PluginManager::scanPlugins(const std::string& directory) {
    if (!fs::exists(directory)) {
        std::cout << "Папка " << directory << " не найдена. Плагины не загружены.\n";
        return;
    }
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".dll") {
            std::string dllPath = entry.path().string(); 
            HMODULE hTempLib = LoadLibraryA(dllPath.c_str());
            if (hTempLib) {
                auto getFuncName = (const char*(*)())GetProcAddress(hTempLib, "GetFunctionName");
                if (getFuncName) {
                    std::string funcName = getFuncName();
                    pluginRegistry[funcName] = dllPath;
                    std::cout << "Зарегистрирован плагин для функции: " << funcName << "\n";
                }
                FreeLibrary(hTempLib);
            }
        }
    }
    std::cout << "Всего зарегистрировано плагинов: " << pluginRegistry.size() << "\n";
}
double PluginManager::evaluate(const std::string& funcName, double arg) {
    if (loadedFunctions.find(funcName) != loadedFunctions.end()) {
        return loadedFunctions[funcName](arg);
    }
    if (pluginRegistry.find(funcName) == pluginRegistry.end()) {
        throw std::runtime_error("Функция не найдена: " + funcName);
    }
    std::string dllPath = pluginRegistry[funcName];
    HMODULE hLib = LoadLibraryA(dllPath.c_str());
    if (!hLib) {
        throw std::runtime_error("Не удалось загрузить DLL: " + dllPath);
    }
    auto evalPtr = (double(*)(double))GetProcAddress(hLib, "Evaluate");
    if (!evalPtr) {
        FreeLibrary(hLib);
        throw std::runtime_error("Точка входа 'Evaluate' не найдена в плагине для: " + funcName);
    }
    loadedHandles[funcName] = hLib;
    loadedFunctions[funcName] = evalPtr;
    std::cout << "Плагин '" << funcName << "' загружен по запросу из " << fs::path(dllPath).filename().string() << "\n";
    return evalPtr(arg);
}
std::string PluginManager::evaluateExpression(const std::string& expr) {
    std::string result = expr;
    std::regex reg("([a-zA-Z]+)\\(([^()]+)\\)");
    std::smatch match;
    while (std::regex_search(result, match, reg)) {
        std::string funcName = match[1].str();
        std::string argsStr = match[2].str();
        double arg = calcRef.calculate(argsStr);
        double val = evaluate(funcName, arg); 
        result.replace(match.position(), match.length(), std::to_string(val));
    }
    return result;
}