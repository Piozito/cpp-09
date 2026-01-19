/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:02:32 by aaleixo-          #+#    #+#             */
/*   Updated: 2026/01/12 09:15:48 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return *this;
}

double RPN::getResult(const char *input)
{
    std::stack<double> numbers;
    ssize_t i = 0;
    double num1, num2;

    while (input[i])
    {
        if (std::isspace(input[i]))
        {
            i++;
            continue;
        }
        else if (std::isdigit(input[i]))
            numbers.push(input[i] - '0');
        else if (input[i] == '/' || input[i] == '+' || input[i] == '-' || input[i] == '*')
        {
            if (numbers.size() < 2)
                throw(RPN::IncorrectAmountofNumbersException());

            num2 = numbers.top();
            numbers.pop();
            num1 = numbers.top();
            numbers.pop();

            // std::cout << "Debug: " << num1 << input[i] << num2 << std::endl; // debug

            if (input[i] == '+')
                numbers.push(num1 + num2);
            else if (input[i] == '-')
                numbers.push(num1 - num2);
            else if (input[i] == '*')
                numbers.push(num1 * num2);
            else if (input[i] == '/')
            {
                if (num2 == 0)
                    throw(RPN::DivisionByZeroException());
                numbers.push(num1 / num2);
            }
        }
        else
            throw(RPN::InvalidCharacterException(std::string(1, input[i])));
        i++;
    }
    if (numbers.size() != 1)
        throw(RPN::IncorrectAmountOfArgumentsException());
    return numbers.top();
}