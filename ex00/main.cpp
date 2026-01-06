/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:34:50 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/01/06 17:06:44 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    BitcoinExchange main;

    if (ac != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return -1;
    }

    try
    {
        main.prepDatabase();
        main.execute(av[1]);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}