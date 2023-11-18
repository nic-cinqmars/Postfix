#include <iostream>
#include "Postfix.h"

int main()
{
	std::string input;

	std::cout << "Input a postfix expression (without any spaces) : ";
	std::getline(std::cin, input);

	std::vector<char> expression(input.begin(), input.end());
	
	Postfix p(expression);

	std::cout << "Is the expression valid ? : " << (p.validate() ? "Yes" : "No") << "\n";
	std::cout << "Are the expression's parantheses OK ? : " << (p.parentheses() ? "Yes" : "No") << "\n";

	if (p.validate() && p.parentheses())
	{
		p.transformToNumbers();
		std::cout << "Prefix expression : " << p.getExpression() << "\n";

		p.transformToPostFix();
		std::cout << "Postfix expression : " << p.getExpression() << "\n";

		std::cout << "Evaluated postfix expression : " << p.evaluateExpression();
	}
	else
	{
		std::cout << "Invalid expression!";
	}
}