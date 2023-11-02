#include "include.hpp"


std::vector<std::string> into_RPN(const std::string& infix) { //Функция для переводa инфиксной нотации в обратную польскую
    if (!infix.size()) {
        throw "You have input empty string. Please, try again";
    }
    std::string alph = "qwertyuiopasdfghjklzxcvbnm";
    std::vector<std::string> functions = { "sin", "cos", "tg", "ctg" };
    std::vector<std::string> constants = { "pi", "e", "x" };
    std::vector<std::string> minus = { "m" };
    std::vector<std::string> nums = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "." };
    std::stack<std::string> operator_stack;
    std::map<std::string, int> operators = { {"+", 2}, {"-", 2}, {"*", 1}, {"/", 1}, {"^", 0}, {"m", -1} };
    std::vector<std::string> rpn;
    for (int i = 0; i < infix.size(); ++i) {
        if (std::find(minus.begin(), minus.end(), infix.substr(i, 1)) != minus.end()) {
            operator_stack.push(infix.substr(i, 1));
        }
        else if (operators.count(infix.substr(i, 1))) {
            while ((operator_stack.size()) && (operator_stack.top() != "(") &&
                (operators[infix.substr(i, 1)] >= operators[operator_stack.top()])) {
                rpn.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(infix.substr(i, 1));
        }
        else if (infix[i] == '(') {
            operator_stack.push(infix.substr(i, 1));
        }
        else if (infix[i] == ')') {
            if (operator_stack.size() == 0) {
                throw "Parenthesis sequence in entered expression is wrong!";
            }
            while (operator_stack.top() != "(") {
                rpn.push_back(operator_stack.top());
                operator_stack.pop();
                if (operator_stack.size() == 0) {
                    throw "Parenthesis sequence in entered expression is wrong!";
                }
            }
            operator_stack.pop();
            if (operator_stack.size()) {
                if (std::find(minus.begin(), minus.end(), operator_stack.top()) != minus.end()) {
                    rpn.push_back(operator_stack.top());
                    operator_stack.pop();
                }

            }
        }
        else if (std::find(nums.begin(), nums.end(), infix.substr(i, 1)) != nums.end()) {
            std::string temp = "";
            temp += infix.substr(i, 1);
            while (std::find(nums.begin(), nums.end(), infix.substr(i + 1, 1)) != nums.end()) {
                ++i;
                temp += infix.substr(i, 1);
            }
            rpn.push_back(temp);
        }
        else if (alph.find(infix.substr(i, 1)) != std::string::npos) {
            std::string temp = "";
            temp += infix.substr(i, 1);
            while (alph.find(infix.substr(i + 1, 1)) != std::string::npos) {
                ++i;
                temp += infix.substr(i, 1);
                if (i > infix.size() - 1) {
                    break;
                }
            }
            if ((std::find(constants.cbegin(), constants.cend(), temp)) != constants.end()) {
                rpn.push_back(temp);
            }
            else if ((std::find(functions.cbegin(), functions.cend(), temp)) != functions.end()) {
                operator_stack.push(temp);
            }
            else {
                throw "It seems that you have input constant value or function this calculator does not support. Please try again";
            }
        }
    }
    while (operator_stack.size()) {
        if (operator_stack.top() == "(") {
            throw "Parenthesis sequence in entered expression is wrong!";
        }
        rpn.push_back(operator_stack.top());
        operator_stack.pop();
    }
    return rpn;
}