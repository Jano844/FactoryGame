NAME = game


CXX			= g++
CXXFLAGS	= -Wall -Wextra -std=c++11
LIBS		= -lsfml-graphics -lsfml-window -lsfml-system

SRCS		=	main.cpp \
				Game.cpp \
				Player.cpp \
				AssemblyLine.cpp



OBJS		= $(SRCS:.cpp=.o)


all: $(NAME)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LIBS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all fclean



