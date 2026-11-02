#include "BitcoinExchange.hpp"
#include <iostream>




int	main(int argc, char **argv)
{
	BitcoinExchange btc;

	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	if (!btc.loadDataBase("data.csv"))
	{
		std::cerr << "Error: file could not be load" << std::endl;
		return (1);
	}
	if (!btc.processInput(argv[1]))
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
}
