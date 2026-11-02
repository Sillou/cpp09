#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <list>


class RPN
{
private:
	std::stack<int, std::list<int> >	_stack;

	bool	_applyOperator(char op);

public:
	RPN( void );
	RPN(RPN const &src);
	RPN &operator=(RPN const &src);
	~RPN();

	bool	evaluate(std::string const &expr, int &result);
};




#endif
