/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:56:44 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/02/24 09:40:37 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <stack>

class RPN
{
private:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);

public:
    ~RPN();

    static double getResult(const char *input);

    class InvalidCharacterException : public std::exception
    {
    private:
        std::string _error;

    public:
        InvalidCharacterException(std::string error) : _error("Invalid character -> " + error) {}
        virtual ~InvalidCharacterException() throw() {}
        const char *what() const throw()
        {
            return (this->_error.c_str());
        }
    };
    class DivisionByZeroException : public std::exception
    {
        const char *what() const throw()
        {
            return "A number cannot be divided by '0'";
        }
    };
    class IncorrectAmountOfArgumentsException : public std::exception
    {
        const char *what() const throw()
        {
            return "Incorrect amount of arguments, there should be one more numbers than operators.";
        }
    };
    class IncorrectAmountofNumbersException : public std::exception
    {
        const char *what() const throw()
        {
            return "There should be atleast 2 numbers in the stack per operation, (2 2 +) not (2 + 2)";
        }
    };
	class InvalidSpaceException : public std::exception
    {
        const char *what() const throw()
        {
            return "Every argument should be separated by a space.";
        }
    };
};

#endif
