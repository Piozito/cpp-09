/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:17:25 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/01/19 22:41:29 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool checkNum(char *str)
{
    for(ssize_t i = 0; str[i]; i++)
    {
        if(!std::isdigit(str[i]))
            return false;
    }
    return true;
}

char checkDup(char **av, ssize_t i)
{
    for(ssize_t j = 1; j < i; j++)
    {
        if(std::string(av[j]) == std::string(av[i]))
            return false;
    }
    return true;
}

bool checkInput(char **av)
{
    for(ssize_t i = 1; av[i]; i++)
    {
        std::string temp = av[i];
        if(checkDup(av, i) == false)
            return false;
        if(std::find(temp.begin(), temp.end(), '-') != temp.end())
            return false;
        if(checkNum(av[i]) == false)
            return false;
        if(std::atol(av[i]) > INT_MAX || std::atol(av[i]) < INT_MIN)
            return false;
    }
    return true;
}