# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/30 00:32:59 by aaleixo-          #+#    #+#              #
#    Updated: 2026/01/12 09:16:52 by aaleixo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe
SOURCES = \
	main.cpp PmergeMe.cpp
OBJECTS = $(SOURCES:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re