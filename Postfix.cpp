#include "Postfix.h"

bool Postfix::validate() const
{
    for (const char& c : expression)
    {
        if (isdigit(c))
            continue;

        switch (c)
        {
            case '(':
            case ')':
            case '*':
            case '/':
            case '%':
            case '+':
            case '-':
                continue;
            default:
                return false;
        }
    }
    return true;
}

bool Postfix::parentheses() const
{
    if (std::count(expression.begin(), expression.end(), '(') == std::count(expression.begin(), expression.end(), ')'))
        return true;
    else
        return false;
}

/*  
    Converts all operands (numbers composed of 1 or more digits) in the expression vector to the char 'o' and stores their value in the operands stack.
    The first operand in the expression is put at the top of the stack.
*/
void Postfix::transformToNumbers()
{
    std::string currentNumber = "";

    // Temporary stack for all our operands, in the reverse order that we need them
    std::stack<int> reversedOperands;

    // Read vector backwards so operands are in the correct order that they are needed from the stack
    for (auto it = expression.begin(); it != expression.end();)
    {
        char currentChar = *it;

        if (isdigit(currentChar))
        {
            if (currentNumber.empty()) // If this is the first digit of a number, change it to 'o'
            {
                *it = 'o';
                ++it; // Go to next char in the vector
            }
            else
                it = expression.erase(it); // If it is not the first digit of a number, remove it from the vector and go to the next char in the vector

            currentNumber += currentChar;
        }
        else
        {
            if (!currentNumber.empty()) // If it is not a digit and currentNumber != "", we have a complete number
            {
                reversedOperands.push(std::stoi(currentNumber));
                currentNumber = "";
            }
            ++it; // Go to the next char in the vector
        }
    }

    if (!currentNumber.empty()) // If last char in vector was a digit, this number is not yet added to the reversedOperands stack
        reversedOperands.push(std::stoi(currentNumber));

    while (!reversedOperands.empty())
    {
        operands.push(reversedOperands.top()); // Add to our operands stack, in the proper order (
        reversedOperands.pop();
    }
}

int Postfix::precedence(const char& op) const
{
    if (op == '/' || op == '*' || op == '%')
        return 1;
    else if (op == '+' || op == '-')
        return 0;
    else
        return -1;
}

void Postfix::transformToPostFix()
{
    // From course theory

    std::vector<char> postFix;
    std::stack<char> s;
    for (const char& c : expression)
    {
        if (c == 'o')
            postFix.push_back(c);
        else if (c == '(')
            s.push('(');
        else if (c == ')')
        {
            while (s.top() != '(')
            {
                postFix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else
        {
            while (!s.empty() && precedence(c) <= precedence(s.top()))
            {
                postFix.push_back(s.top());
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty())
    {
        postFix.push_back(s.top());
        s.pop();
    }

    expression = postFix;
}

std::string Postfix::getExpression() const
{
    std::string expressionString = "";

    // Create a copy of operands stack to not lose our original stack
    std::stack<int> tempOperands = operands;

    for (const char& c : expression)
    {
        if (c == 'o')
        {
            expressionString += std::to_string(tempOperands.top()) + " ";
            tempOperands.pop();
        }
        else
        {
            expressionString += c;
            expressionString += " ";
        }
    }

    return expressionString;
}

int Postfix::evaluateExpression() const
{
    std::stack<int> s;

    // Create a copy of operands stack to not lose our original stack
    std::stack<int> tempOperands = operands;

    // From course theory

    for (const char& c : expression)
    {
        if (c == 'o')
        {
            s.push(tempOperands.top());
            tempOperands.pop();
        }
        else
        {
            int x = s.top();
            s.pop();

            int y = s.top();
            s.pop();

            switch (c) 
            {
            case '+':
                s.push(y + x);
                break;
            case '-':
                s.push(y - x);
                break;
            case '*':
                s.push(y * x);
                break;
            case '/':
                s.push(y / x);
                break;
            case '%':
                s.push(y % x);
                break;
            }
        }
    }

    return s.top();
}
