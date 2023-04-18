##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile for SFML
##

SRC_PATH			=	./src/

SRC_PATH_PIZZA 		=	./src/pizzas/

SRC_PATH_COMMAND 	=	./src/command/

SRC_PATH_PROCESS 	=	./src/process/

SRC_PATH_EXCEPTION 	=	./src/exceptions/

SRC_PATH_IPC 		=	./src/ipc/

SRC_PATH_THREAD 	=	./src/threads/

SRC_PATH_COOK		= 	./src/cooks/

SRC_PATH_KITCHEN		= 	./src/kitchen/

SRC					=	main.cpp														\
						$(addprefix $(SRC_PATH), Reception.cpp)							\
						$(addprefix $(SRC_PATH_COOK), Cook.cpp)							\
						$(addprefix $(SRC_PATH_KITCHEN), Ingredients.cpp)				\
						$(addprefix $(SRC_PATH_KITCHEN), Kitchens.cpp)					\
						$(addprefix $(SRC_PATH_PIZZA), PizzaAmericana.cpp)				\
						$(addprefix $(SRC_PATH_PIZZA), Pizza.cpp)						\
						$(addprefix $(SRC_PATH_PIZZA), PizzaFantasia.cpp)				\
						$(addprefix $(SRC_PATH_PIZZA), PizzaMargarita.cpp)				\
						$(addprefix $(SRC_PATH_PIZZA), PizzaRegina.cpp)					\
						$(addprefix $(SRC_PATH_COMMAND), Command.cpp)					\
						$(addprefix $(SRC_PATH_EXCEPTION), MutexException.cpp)			\
						$(addprefix $(SRC_PATH_PROCESS), process.cpp)					\
						$(addprefix $(SRC_PATH_PROCESS), ChildProcess.cpp)				\
						$(addprefix $(SRC_PATH_PROCESS), SafeQueue.cpp)					\
						$(addprefix $(SRC_PATH_IPC), NamedPipe.cpp)

override CXXFLAGS	+=	-W -Wall -Wextra -g

override CPPFLAGS	+=	-I./ 					\
						-I./src/pizzas			\
						-I./src					\
						-I./src/command			\
						-I./src/process			\
						-I./src/ipc				\
						-I./src/exceptions		\
						-I./src/cooks			\
						-I./src/kitchen

OBJ					=	$(SRC:.cpp=.o)

NAME				=	plazza

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) -lpthread -lrt

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:: fclean
re:: all

.PHONY:	all clean fclean re
