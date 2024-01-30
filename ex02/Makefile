NAME = PmergeMe

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS = main.cpp src/PmergeMe.cpp
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all : obj $(NAME)

obj :
	@mkdir -p obj

obj/%.o : src/%.cpp | obj
	@c++ $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(SRCS)
	@c++ $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[32m$(NAME) is created\033[0m"

clean :
	rm -rf obj

fclean : clean
	rm -f $(NAME)

re: fclean all

run : fclean all
	./$(NAME) 3 5 9 7 4