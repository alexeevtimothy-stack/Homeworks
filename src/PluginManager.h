#pragma once

#include <string>
#include <map>
#include <filesystem>
#include <windows.h>
#include "IPlugin.h"
#include "Calculator.h"

class PluginManager {
    std::map<std::string, std::string> pluginRegistry;
    std::map<std::string, HMODULE> loadedHandles;
    std::map<std::string, EvaluateFn> loadedFunctions;
    Calculator& calcRef;
public:
    explicit PluginManager(Calculator& calc);
    void scanPlugins(const std::string& directory);
    double evaluate(const std::string& funcName, double arg);
    std::string evaluateExpression(const std::string& expr);
};