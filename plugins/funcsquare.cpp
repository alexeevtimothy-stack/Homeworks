#include "IPlugin.h"
#include <cmath>

extern "C" {
    PLUGIN_EXPORT const char* GetFunctionName() {
        return "sqr"; 
    }
    PLUGIN_EXPORT double Evaluate(double arg) {
        return arg * arg;
    }
}