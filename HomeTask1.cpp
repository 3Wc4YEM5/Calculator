#include "include.hpp"
#include "intoRPN.hpp"
#include "calculate_RPN.hpp"


std::string delete_space(const std::string& infix) {  //Удаляет лишние пробелы из строки
    std::string ans = "";
    for (auto& el : infix) {
        if (el != ' ') {
            ans += el;
        }
    }
    return ans;
}

void transform_infix(std::string& infix) {    //Превращает минусы, означающие отрицательные значения, а не вычитание в функцию
    infix = delete_space(infix);
    std::string operators = "+-*/^nsgp";
    if (infix[0] == '-') {
        infix[0] = 'm';
    }
    char temp = ' ';
    if ((infix[0] != '(') && (infix[0] != ')')) {
        temp = infix[0];
    }
    for (int i = 1; i < infix.size(); ++i) {
        if (temp != ' ') {
            if ((infix[i] == '-') && (std::find(operators.begin(), operators.end(), temp) != operators.end())) {
                infix[i] = 'm';
            }
            if ((infix[i] != '(') && (infix[i] != ')')) {
                temp = infix[i];
            }
        }
        else {
            if (infix[i] == '-') {
                infix[i] = 'm';
            }
            if ((infix[i] != '(') && (infix[i] != ')')) {
                temp = infix[i];
            }
        }
    }
}


int main()
{
    std::string infix = "";
    std::vector<std::string> rpn;
    std::cout << "To write down expression use:" << std::endl << "'+' to add" << std::endl << "'-' to substract" <<
        std::endl << "'*' to multiply" << std::endl << "'/' to divide" << std::endl << "'.' to write fractional numbers" << std::endl
        << "'(' and ')' to set order of calculations" << std::endl << "'pi' and 'e' to enter Pi number and Euler number respectively" << std::endl
        << "You may use functions such as 'sin()', 'cos()', 'tg()', 'ctg()' and 'exp()'" << std::endl;
    std::cout << "Are you going to use 'x' in this expression? Input value of x if you are and press 'Enter' otherwise ";
    std::string temp = ""; std::getline(std::cin, temp);
    float x;
    if (temp != "") {
        x = std::stof(temp);
    }
    else {
        x = 0;
    }
    std::cout << "Enter your expression below. You may input 'q' to quit calculator" << std::endl;
    std::getline(std::cin, infix);
    while (infix != "q") {
        try {
            transform_infix(infix);
            rpn = into_RPN(infix);
            std::cout << "Result of your expression: " << calculate_rpn(rpn, x) << std::endl;
        }
        catch (const char* error_message) {
            std::cout << error_message << std::endl;
        }
        std::cout << "Are you going to use 'x' in this expression? Input value of x if you are and press 'Enter' otherwise ";
        std::string temp = ""; std::getline(std::cin, temp);
        if (temp != "") {
            x = std::stof(temp);
        }
        else {
            x = 0;
        }
        std::cout << "Enter your expression below: " << std::endl;
        std::getline(std::cin, infix);
        transform_infix(infix);
    }
    return 0;
}
