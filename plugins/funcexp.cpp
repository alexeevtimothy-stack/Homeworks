#include "IPlugin.h"
#include <cmath>

extern "C" {
    PLUGIN_EXPORT const char* GetFunctionName() {
        return "exp";
    }
    PLUGIN_EXPORT double Evaluate(double arg) {
        return std::exp(arg);
    }
}