/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:17:06 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/01/19 23:08:46 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <list>
#include <deque>

int main(int ac, char **av)
{
    if(ac < 2 || checkInput(av) == false)
    {
        std::cerr << "Invalid input." << std::endl;
        std::cerr << "Usage: N, N, N, N, N where N stand for positive integers." << std::endl;
        return -1;
    }

    std::cout << "Before:\t";
    for (int i  = 1; av[i]; i++)
        std::cout << av[i] << " ";
    std::cout << std::endl;

    fordJohnsonSort<std::list> list_test;
    fordJohnsonSort<std::deque> deque_test;

    try
    {
        clock_t before_ls = clock();

        list_test.sort(av);
        
        std::cout << "After:\t";
        list_test.display();

        std::cout << "Time to process a range of " << ac - 1 << " elements with std::list : " << std::fixed << std::setprecision(5) << static_cast<double>(clock() - before_ls) / CLOCKS_PER_SEC<< " seconds." << std::endl;
     
        clock_t before_dq = clock();

        deque_test.sort(av);
        std::cout << "Time to process a range of " << ac - 1 << " elements with std::deque : " << std::fixed << std::setprecision(5) << static_cast<double>(clock() - before_dq) / CLOCKS_PER_SEC<< " seconds." << std::endl;

        //list_test.check();
        //deque_test.check();
    }
    catch(std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
}

