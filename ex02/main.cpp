/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:29:09 by alubrano          #+#    #+#             */
/*   Updated: 2026/11/02 16:29:10 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	PmergeMe	pm;

	if (!pm.parse(argc, argv))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	pm.run();
	return (0);
}
