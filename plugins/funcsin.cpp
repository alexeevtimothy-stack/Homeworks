#include "IPlugin.h"
#include <cmath>

extern "C" {
    PLUGIN_EXPORT const char* GetFunctionName() {
        return "sin";
    }
    PLUGIN_EXPORT double Evaluate(double arg) {
        double rad = arg * 3.14159265358979323846 / 180.0;
        return std::sin(rad);
    }
}