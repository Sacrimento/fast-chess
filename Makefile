NAME		=	fast-chess
FLAGS		= 	-std=c++17 -Wextra -lX11 -lGL -lpthread -lpng -lstdc++fs
COMPILER	=	g++

DIR_INC		=	./inc/
DIR_SRC		=	./src/
DIR_OBJ		= 	./obj/

HEAD_MD	=		olcPixelGameEngine.h \
				ChessInterface.h \
				Board.h \
				Piece.h

SRC_MD		=	main.cpp \
			Board.cpp \
			ChessInterface.cpp

INC_PATH 	= 	$(addprefix $(DIR_INC), $(HEAD_MD))

OBJ 		= 	$(addprefix $(DIR_OBJ), $(SRC_MD:.cpp=.o))
INC 		= 	$(addprefix -I, $(DIR_INC))

.PHONY: all obj $(NAME) clean fclean re

all: obj $(NAME)

obj:
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ) $(FLAGS)

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp $(INC_PATH)
	$(COMPILER) $(FLAGS) $(INC) -c -o $@ $<

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
