/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:28:57 by alubrano          #+#    #+#             */
/*   Updated: 2026/11/02 16:28:58 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	RPN	rpn;
	int	result;

	if (!rpn.evaluate(argv[1], result))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	std::cout << result << std::endl;
	return (0);
}
