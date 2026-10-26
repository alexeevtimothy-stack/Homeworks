#include "IPlugin.h"
#include <cmath>
#include <stdexcept>

extern "C" {
    PLUGIN_EXPORT const char* GetFunctionName() {
        return "ln";
    }
    PLUGIN_EXPORT double Evaluate(double arg) {
        if (arg <= 0) {
            throw std::domain_error("Аргумент логарифма должен быть больше 0");
        }
        return std::log(arg);
    }
}