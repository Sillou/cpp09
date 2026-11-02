#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cctype>





BitcoinExchange::BitcoinExchange( void )
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) : _map(src._map)
{

}
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &src)
{
	if (this != &src)
		_map = src._map;
	return (*this);
}
bool	BitcoinExchange::loadDataBase(std::string const &filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file.is_open())
		return (false);
	std::getline(file,line);
	while (std::getline(file, line))
	{
		size_t	pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string	date = line.substr(0, pos);
		std::string rateStr = line.substr(pos + 1);
		float	rate = std::atof(rateStr.c_str());
		_map[date] = rate;
	}
	if (_map.empty())
		return (false);
	return (true);
}

bool	BitcoinExchange::processInput( std::string const &filename) const
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file.is_open())
		return (false);
	bool	first = true;

	while (std::getline(file, line))
	{
		if (first)
		{
			first = false;
			if (line == "date | value")
				continue;
		}
		size_t	pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string	date = line.substr(0, pos);
		std::string	valueStr = line.substr(pos + 3);
		float		value;

		if (!_isValideDate(date) || date < _map.begin()->first)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (!_parseValue(valueStr, value))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << value * _getRate(date) << std::endl;
	}
	if (first)
		return (false);
	return (true);
}

bool	BitcoinExchange::_isValideDate(std::string const &date) const
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for(size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return (false);
	}
	std::string yearStr = date.substr(0, 4);
	int	year = std::atoi(yearStr.c_str());

	std::string	monthStr = date.substr(5, 2);
	int	month = std::atoi(monthStr.c_str());
	if (month < 1 || month > 12)
		return (false);

	int	dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		dayInMonth[1] = 29;

	std::string dayStr = date.substr(8, 2);
	int	day = std::atoi(dayStr.c_str());
	if (day > dayInMonth[month-1] || day < 1)
		return (false);

	return (true);
}

bool	BitcoinExchange::_parseValue(std::string const &str, float &value) const
{
	char *end;

	if (str.empty())
		return (false);
	for(size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '-' && i == 0)
			continue;
		if (!std::isdigit(str[i]) && str[i] != '.')
			return (false);
	}
	double	result = std::strtod(str.c_str(), &end);
	if (*end != '\0')
		return (false);
	value = static_cast<float>(result);
	return (true);
}

float	BitcoinExchange::_getRate(std::string const &date) const
{
	std::map<std::string, float>::const_iterator	it = _map.lower_bound(date);
	if (it == _map.end() || it->first != date)
		it--;
	return (it->second);
}

