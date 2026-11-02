#include "RPN.hpp"
#include <sstream>
#include <cctype>
#include <climits>

RPN::RPN( void )
{
}

RPN::~RPN()
{
}

RPN::RPN(RPN const &src) : _stack(src._stack)
{

}

RPN &RPN::operator=(RPN const &src)
{
	if (this != &src)
		_stack = src._stack;
	return (*this);
}

bool	RPN::_applyOperator(char op)
{
	if (_stack.size() < 2)
		return (false);
	int	b = _stack.top();
	_stack.pop();
	int	a = _stack.top();
	_stack.pop();
	long	res = 0;

	if (op == '+')
		res = static_cast<long>(a) + b;
	else if(op == '-')
		res = static_cast<long>(a) - b;
	else if(op == '*')
		res = static_cast<long>(a) * b;
	else if(op == '/')
	{
		if (b == 0)
			return (false);
		res = static_cast<long>(a) / b;
	}
	if (res > INT_MAX || res < INT_MIN)
		return (false);
	_stack.push(static_cast<int>(res));
	return (true);
}

bool	RPN::evaluate(std::string const &expr, int &result)
{
	std::istringstream	iss(expr);
	std::string			token;

	while (!_stack.empty())
		_stack.pop();

	while (iss >> token)
	{
		if (token.length() != 1)
			return (false);
		if (std::isdigit(token[0]))
			_stack.push(token[0] - '0');
		else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
		{
			if (!_applyOperator(token[0]))
			return (false);
		}
		else
		return (false);
	}
	if (_stack.size() != 1)
		return (false);
	result = _stack.top();
	return (true);
}
