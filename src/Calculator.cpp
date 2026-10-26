#include "Calculator.h"
#include <stdexcept>
#include <cctype>

class Parser {
    const std::string& str;
    size_t pos = 0;
    void skipWhitespace() {
        while (pos < str.length() && std::isspace(str[pos])) {
            pos++;
        }
    }
    double parseNumber() {
        skipWhitespace();
        size_t start = pos;
        bool hasDecimal = false;
        if (pos < str.length() && (str[pos] == '+' || str[pos] == '-')) {
            pos++;
        }
        while (pos < str.length() && (std::isdigit(str[pos]) || str[pos] == '.')) {
            if (str[pos] == '.') hasDecimal = true;
            pos++;
        }
        if (start == pos) {
            throw std::runtime_error("Ожидалось число в выражении");
        }
        return std::stod(str.substr(start, pos - start));
    }
    double parseFactor() {
        skipWhitespace();
        if (pos < str.length() && str[pos] == '(') {
            pos++;
            double val = parseExpression();
            skipWhitespace();
            if (pos < str.length() && str[pos] == ')') {
                pos++; 
            }
            return val;
        }
        return parseNumber();
    }
    double parseTerm() {
        double val = parseFactor();
        while (true) {
            skipWhitespace();
            if (pos >= str.length()) break;
            char op = str[pos];
            if (op != '*' && op != '/') break;
            pos++;
            double nextVal = parseFactor();
            if (op == '*') val *= nextVal;
            else {
                if (nextVal == 0) throw std::runtime_error("Деление на ноль");
                val /= nextVal;
            }
        }
        return val;
    }
    double parseExpression() {
        double val = parseTerm();
        while (true) {
            skipWhitespace();
            if (pos >= str.length()) break;
            char op = str[pos];
            if (op != '+' && op != '-') break;
            pos++;
            double nextVal = parseTerm();
            if (op == '+') val += nextVal;
            else val -= nextVal;
        }
        return val;
    }
public:
    explicit Parser(const std::string& s) : str(s) {}
    double parse() {
        double result = parseExpression();
        skipWhitespace();
        if (pos < str.length()) {
            throw std::runtime_error("Лишние символы в выражении");
        }
        return result;
    }
};
double Calculator::calculate(const std::string& expression) {
    Parser parser(expression);
    return parser.parse();
}