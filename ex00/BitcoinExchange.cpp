/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:36:30 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/01/20 16:31:29 by aaleixo-         ###   ########.fr       */
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
    {
        this->dbase = other.dbase;
        this->data = other.data;
    }
    return *this;
}

bool BitcoinExchange::_checkLeapYear(int year)
{
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        return true;
    return false;
}

bool BitcoinExchange::_checkDay(int month, int day)
{
    if((month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12) && day <= 31)
        return true;
    else if(day <= 30)
        return true;
    return false;
}

bool BitcoinExchange::_checkDate(std::string date)
{
    if (date.size() != 10 && !(date.size() == 11 && date[date.size() - 1] == ' '))
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    if ((date[5] >= '1' && date[6] > '2') || (date[5] == '0' && date[6] == '0'))
        return false;

    if (this->_checkDay(std::atoi(date.substr(5, 6).c_str()), std::atoi(date.substr(8, 9).c_str())) == false)
        return false;

        
    if (this->_checkLeapYear(std::atoi(date.substr(0, 4).c_str())) == true)
    {
        if (date[5] == '0' && date[6] == '2' && date[8] >= '2' && date[9] > '9')
            return false;
    }
    else
    {
        if (date[5] == '0' && date[6] == '2' && date[8] >= '2' && date[9] > '8')
            return false;
    }
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

    if (!file.is_open())
        throw(BitcoinExchange::FileErrorException());
    std::getline(file, line);
    if (line != "date | value")
        throw(BitcoinExchange::NoHeaderException());
    while (std::getline(file, line))
    {
        try
        {
            if (line.find('|') == line.npos)
                throw(BitcoinExchange::InvalidInputException("Divider character not found \"|\"."));
            date = line.substr(0, (line.find('|')));
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
