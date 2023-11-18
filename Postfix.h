#pragma once
#include <stack>
#include <vector>
#include <ctype.h>
#include <string>

class Postfix
{
private:
	std::stack<int> operands;
	std::vector<char> expression;

public:
	Postfix(const std::vector<char>& expression) : expression(expression) { };

	bool validate() const;
	bool parentheses() const;

	int precedence(const char& op) const;
	void transformToNumbers();
	void transformToPostFix();

	std::string getExpression() const;

	int evaluateExpression() const;
};