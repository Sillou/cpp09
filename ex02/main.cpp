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
