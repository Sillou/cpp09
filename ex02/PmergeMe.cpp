/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:29:12 by alubrano          #+#    #+#             */
/*   Updated: 2026/11/02 16:29:13 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <climits>
#include <cctype>
#include <cstdlib>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iomanip>


PmergeMe::PmergeMe( void )
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	_input = src._input;
	_vec = src._vec;
	_deque = src._deque;
}


PmergeMe &PmergeMe::operator=(PmergeMe const &src)
{
	if (this != &src)
	{
		_input = src._input;
		_vec = src._vec;
		_deque = src._deque;
	}
	return (*this);
}


bool	PmergeMe::parse(int argc, char **argv)
{
	if (argc < 2)
		return (false);
	for (int i = 1; i < argc; i++)
	{
		std::string	arg = argv[i];

		if (arg.empty())
			return (false);
		for (size_t j = 0; j < arg.length(); j++)
		{
			if (!std::isdigit(arg[j]))
				return (false);
		}
		long	n = std::strtol(arg.c_str(), NULL, 10);
		if (n > INT_MAX)
			return (false);
		_input.push_back(static_cast<int>(n));
	}
	return (true);
}

void	PmergeMe::run()
{
	std::cout << "Before:";
	for (size_t i = 0; i < _input.size(); i++)
		std::cout << " " << _input[i];
	std::cout << std::endl;


	clock_t start = clock();

	_vec.assign(_input.begin(), _input.end());
	_sortVector(_vec);
	clock_t end = clock();
	double	timeVec = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;

	start = clock();
	_deque.assign(_input.begin(), _input.end());
	_sortDeque(_deque);
	end = clock();
	double	timeDeq = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;


	std::cout << "After:";
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << " Time to process a range of " << _input.size()
			<< " elements with std::vector : " << timeVec<< " us" << std::endl;
	std::cout << " Time to process a range of " << _input.size()
			<< " elements with std::deque : " << timeDeq<< " us" << std::endl;



}

void	PmergeMe::_sortVector(std::vector<int> &v)
{
	if (v.size() <= 1)
		return ;
	std::vector<std::pair<int, int> >	pairs;

	bool	hasStraggler = (v.size() % 2 != 0);
	int		straggler = 0;

	if (hasStraggler)
		straggler = v.back(); //renvoie le dernier element
	for (size_t i = 0; i + 1 < v.size(); i += 2)
	{
		if (v[i] > v[i + 1])
			pairs.push_back(std::make_pair(v[i], v[i + 1]));
		else
			pairs.push_back(std::make_pair(v[i + 1] , v[i]));
	}

	std::vector<int>	bigs;

	for (size_t i = 0; i < pairs.size(); i++)
		bigs.push_back(pairs[i].first);
	_sortVector(bigs);

	std::vector<int> pend;
	std::vector<bool> used(pairs.size(), false);

	for(size_t i = 0; i < bigs.size(); i++)// re-associer les petits de la paire a bigs
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == bigs[i])
			{
				pend.push_back(pairs[j].second);
				used[j] = true;
				break;
			}
		}
	}

	std::vector<int> mainchain = bigs;
	mainchain.insert(mainchain.begin(), pend[0]);

	size_t	done = 1;
	size_t	jPrev = 1;
	size_t	jCurr = 3;

	while (done < pend.size())
	{
		size_t	end = jCurr;
		if (end > pend.size())
			end = pend.size();
		for (size_t k = end; k > done; k--)
		{
			std::vector<int>::iterator bound = std::lower_bound(mainchain.begin(), mainchain.end(), bigs[k - 1]);
			std::vector<int>::iterator pos = std::lower_bound(mainchain.begin(), bound, pend[k - 1]);
			mainchain.insert(pos, pend[k - 1]);
		}
		done = end;
		size_t next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}
	if (hasStraggler)
		mainchain.insert(std::lower_bound(mainchain.begin(), mainchain.end(), straggler), straggler);
	v = mainchain;
}


void	PmergeMe::_sortDeque(std::deque<int> &v)
{
	if (v.size() <= 1)
		return ;
	std::deque<std::pair<int, int> >	pairs;

	bool	hasStraggler = (v.size() % 2 != 0);
	int		straggler = 0;

	if (hasStraggler)
		straggler = v.back(); //renvoie le dernier element
	for (size_t i = 0; i + 1 < v.size(); i += 2)
	{
		if (v[i] > v[i + 1])
			pairs.push_back(std::make_pair(v[i], v[i + 1]));
		else
			pairs.push_back(std::make_pair(v[i + 1] , v[i]));
	}

	std::deque<int>	bigs;

	for (size_t i = 0; i < pairs.size(); i++)
		bigs.push_back(pairs[i].first);
	_sortDeque(bigs);

	std::deque<int> pend;
	std::deque<bool> used(pairs.size(), false);

	for(size_t i = 0; i < bigs.size(); i++)// re-associer les petits de la paire a bigs
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == bigs[i])
			{
				pend.push_back(pairs[j].second);
				used[j] = true;
				break;
			}
		}
	}

	std::deque<int> mainchain = bigs;
	mainchain.insert(mainchain.begin(), pend[0]);

	size_t	done = 1;
	size_t	jPrev = 1;
	size_t	jCurr = 3;

	while (done < pend.size())
	{
		size_t	end = jCurr;
		if (end > pend.size())
			end = pend.size();
		for (size_t k = end; k > done; k--)
		{
			std::deque<int>::iterator bound = std::lower_bound(mainchain.begin(), mainchain.end(), bigs[k - 1]);
			std::deque<int>::iterator pos = std::lower_bound(mainchain.begin(), bound, pend[k - 1]);
			mainchain.insert(pos, pend[k - 1]);
		}
		done = end;
		size_t next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}
	if (hasStraggler)
		mainchain.insert(std::lower_bound(mainchain.begin(), mainchain.end(), straggler), straggler);
	v = mainchain;
}

