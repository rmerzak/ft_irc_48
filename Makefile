NAME = ircserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

HEADER = ./includes/Server.hpp ./includes/Definition.hpp ./includes/Client.hpp
SRC = main.cpp ./Implementations/Server.cpp ./Implementations/Client.cpp

OBJ = $(SRC:.cpp=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	make clean

all : $(NAME)

%.o : %.cpp $(HEADER)

clean :
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all