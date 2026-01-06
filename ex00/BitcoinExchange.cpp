/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:36:30 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/01/06 17:17:59 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    if (this != &other)
        this->data = other.data;
}

BitcoinExchange::~BitcoinExchange()
{
}

const BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        this->data = other.data;
    return *this;
}

bool BitcoinExchange::_checkDate(std::string date)
{
    if (date.size() != 10 && !(date.size() == 11 && date[date.size() - 1] == ' '))
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    if ((date[5] == '1' && date[6] > '2') || date[5] > '1')
        return false;

    if ((date[8] == '3' && date[9] > '1') || date[8] > '3')
        return false;
    return true;
}

bool BitcoinExchange::_checkValue(float value)
{
    if (value < 0 || value > 1000)
        return false;
    return true;
}

float BitcoinExchange::_findClosest(std::map<std::string, float>::iterator it)
{
    std::map<std::string, float>::iterator closest;

    closest = this->dbase.lower_bound(it->first);
    if (closest->first == it->first)
        return (closest->second * it->second);
    else if (closest == this->dbase.begin())
        throw(BitcoinExchange::InvalidInputException("No earlier date found."));
    --closest;
    return closest->second * it->second;
}

void BitcoinExchange::prepDatabase()
{
    std::ifstream db("data.csv");
    std::string line, date;
    float value;

    if (!db.is_open())
        throw(BitcoinExchange::FileErrorException());
    std::getline(db, line);
    if (line != "date,exchange_rate")
        throw(BitcoinExchange::NoHeaderException());
    while (std::getline(db, line))
    {
        if (line.find(',') == line.npos)
            throw(BitcoinExchange::InvalidInputException("divider character not found \",\"."));

        date = line.substr(0, line.find(','));
        value = std::atof(line.substr(line.find(',') + 1).c_str());

        if (this->_checkDate(date) == false)
            throw(BitcoinExchange::InvalidInputException(date));
        if (value < 0)
            throw(BitcoinExchange::InvalidInputException(line.substr(line.find(',') + 1)));

        this->dbase[date] = value;
    }
    db.close();
}

void BitcoinExchange::execute(std::string input)
{
    std::ifstream file(input.c_str());
    std::string line, date;
    float value, final;

    std::getline(file, line);
    if (line != "date | value")
        throw(BitcoinExchange::NoHeaderException());
    while (std::getline(file, line))
    {
        try
        {
            if (line.find('|') == line.npos)
                throw(BitcoinExchange::InvalidInputException("Divider character not found \"|\"."));
            date = line.substr(0, line.find('|'));
            if (date.empty())
                throw(BitcoinExchange::InvalidInputException("No date found."));
            value = std::atof(line.substr(line.find('|') + 1).c_str());

            if (this->_checkDate(date) == false)
                throw(BitcoinExchange::InvalidInputException("Invalid date: \"" + date + "\" (YYYY-MM-DD)"));
            if (this->_checkValue(value) == false)
                throw(BitcoinExchange::InvalidInputException("Value: \"" + line.substr(line.find('|') + 2) + "\" needs to be between 0 and 1000"));

            this->data[date] = value;
            std::map<std::string, float>::iterator it = this->data.find(line.substr(0, line.find('|')));
            final = this->_findClosest(it);
            std::cout << "\033[32m" << it->first << " => " << it->second << " = " << final << "\033[0m" << std::endl;

            it++;
        }
        catch (std::exception &e)
        {
            std::cout << "\033[31m" << e.what() << "\033[0m" << std::endl;
            continue;
        }
    }
    file.close();
}
