/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:35:21 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/01/06 17:17:46 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <utility>
#include <fstream>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, float> dbase;
    std::map<std::string, float> data;

    bool _checkDate(std::string date);
    bool _checkValue(float value);
    float _findClosest(std::map<std::string, float>::iterator it);

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    ~BitcoinExchange();
    const BitcoinExchange &operator=(const BitcoinExchange &other);

    void execute(std::string input);
    void prepDatabase();

    class FileErrorException : public std::exception
    {
        const char *what() const throw()
        {
            return "Couldn't open file.";
        }
    };
    class NoHeaderException : public std::exception
    {
        const char *what() const throw()
        {
            return "First line isn't \"date | value\".";
        }
    };
    class InvalidInputException : public std::exception
    {
    private:
        std::string _error;

    public:
        InvalidInputException(std::string error) : _error("Invalid input -> " + error) {}
        virtual ~InvalidInputException() throw() {}
        const char *what() const throw()
        {
            return this->_error.c_str();
        }
    };
};

#endif