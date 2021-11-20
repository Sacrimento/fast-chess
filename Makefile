NAME = fast-chess
FLAGS = -std=c++17 -Wextra -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal
COMPILER = g++

SRC_SUBDIRS = engine engine/pieces interface

SRC_DIR = $(addprefix sources/, $(SRC_SUBDIRS))
DIR_OBJ	= $(addprefix obj/, $(SRC_SUBDIRS))

SRC =	$(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
INC =	$(addprefix	-I, $(SRC_DIR))
OBJ =	$(patsubst sources/%.cpp, obj/%.o, $(SRC))

vpath %.cpp $(SRC_DIR)

define make-rule
$1/%.o: %.cpp
	$(COMPILER) $(FLAGS) $(INC) -c $$< -o $$@
endef

.PHONY: all obj $(NAME) clean fclean re

all: $(DIR_OBJ) $(NAME)

$(DIR_OBJ):
	@mkdir -p $@

$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ) $(FLAGS)

clean:
	@rm -rf obj/

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(foreach bdir,$(DIR_OBJ),$(eval $(call make-rule,$(bdir))))
