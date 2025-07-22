NAME := philo

CC := cc

CFLAGS = -Wall -Werror -Wextra -g

SRC_PATH := src/

SRC := check.c \
		init.c \
		main.c \
		params.c \
		routine.c \
		simulation.c \
		utils.c \
		error.c

SRCS  := $(SRC_PATH)$(SRC)

OBJ_PATH := obj/
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_PATH),$(OBJ))

INC_PATH := -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
	@echo "Compiling philo..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_PATH)
	@echo "philo is ready"

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "Removing philo..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean