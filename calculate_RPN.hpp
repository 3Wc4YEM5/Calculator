#include "include.hpp"

float math_one(const float& x, const std::string& operator_) {  //Функция выполняющая функцию над аргументом
    std::map<std::string, int> ops = { {"m", 1}, {"sin", 2}, {"cos", 3}, {"tg", 4}, {"tg", 5} };
    int var = ops[operator_];
    switch (var) {
        case 1:
            return (x * (-1));
        case 2:
            return sin(x);
        case 3:
            return cos(x);
        case 4:
            return tan(x);
        case 5:
            return 1/tan(x);
    }
}

float math_two(const float& x, const float& y, const std::string& operator_) {  //Функция выполняющая опреации с операндами
    std::map<std::string, int> ops = { {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}, {"^", 5} };
    int var = ops[operator_];
    switch (var) {
    case 1:
        return x + y;
    case 3:
        return x * y;
    case 4:
        return x / y;
    case 2:
        return x - y;
    case 5:
        return pow(x, y);
    }
}


float calculate_rpn(const std::vector<std::string>& rpn, const float& x) {   //Функция подсчёта ОПЗ
    std::vector<float> operand_stack;
    std::map<std::string, int> operators_count = { {"+", 2}, {"-", 2}, {"*", 2}, {"/", 2}, {"^", 2},  {"m", 1}, {"sin", 1}, {"cos", 1}, {"tg", 1}, {"ctg", 1} };
    std::vector<float> temp;
    for (int i = 0; i < rpn.size(); ++i) {
        if (!operators_count.count(rpn[i])) {
            if (rpn[i] == "pi") {
                operand_stack.push_back(M_PI);
            }
            else if (rpn[i] == "e") {
                operand_stack.push_back(M_E);
            }
            else if (rpn[i] == "x") {
                operand_stack.push_back(x);
            }
            else {
                operand_stack.push_back((std::stof(rpn[i])));
            }
        }
        else {
            for (int j = operators_count[rpn[i]] - 1; j > -1; --j) {
                temp.push_back(operand_stack[operand_stack.size() - 1 - j]);
            }
            for (int j = operators_count[rpn[i]] - 1; j > -1; --j) {
                operand_stack.pop_back();
            }
            if (operators_count[rpn[i]] == 2) {
                operand_stack.push_back(math_two(temp[0], temp[1], rpn[i]));
            }
            else {
                operand_stack.push_back(math_one(temp[0], rpn[i]));
            }
            temp.clear();
        }
    }
    return operand_stack.back();
}