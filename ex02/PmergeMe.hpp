/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:29:13 by alubrano          #+#    #+#             */
/*   Updated: 2026/11/02 16:29:14 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class PmergeMe
{
private:
	std::vector<int>	_input;
	std::vector<int>	_vec;
	std::deque<int>		_deque;

	void	_sortVector(std::vector<int> &v);
	void	_sortDeque(std::deque<int> &d);
public:
	PmergeMe( void );
	PmergeMe(PmergeMe const &src);
	PmergeMe &operator=(PmergeMe const &src);
	~PmergeMe();

	bool	parse(int argc, char **argv);
	void	run();
};




#endif
