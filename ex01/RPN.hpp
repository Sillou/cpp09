/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:29:07 by alubrano          #+#    #+#             */
/*   Updated: 2026/11/02 16:29:08 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
