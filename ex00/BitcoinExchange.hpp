#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>



class BitcoinExchange
{
private:
	std::map<std::string, float>	_map;

	bool	_isValideDate(std::string const &date) const;
	bool	_parseValue(std::string const &str, float &value) const;
	float	_getRate(std::string const &date) const;

public:
	BitcoinExchange( void );
	BitcoinExchange(BitcoinExchange const &src);
	BitcoinExchange &operator=(BitcoinExchange const &src);
	~BitcoinExchange();

	bool	loadDataBase(std::string const &filename);
	bool	processInput(std::string const &filename) const;




};

#endif
