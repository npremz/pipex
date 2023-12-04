NAME = pipex

HEADER = ./

SOURCES = main.c free_utils.c

OBJECTS = $(SOURCES:.c=.o)

LIB = libft.a

GCC_FLAGS = -Wall -Wextra -Werror

CC = cc

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB)
	@make display
	@echo "Compiling $(NAME)..."
	@$(CC) $(GCC_FLAGS) $(OBJECTS) $(LIB) -o $(NAME)
	@echo "\033[0;32m"
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"
	@echo "\033[0m"
	@make usage

$(OBJECTS): $(SOURCES)
	@$(CC) $(GCC_FLAGS) -c -I $(HEADER) ${@:.o=.c} -o $@

$(LIB):
	@echo "Compiling Libft..."
	@make -C libft
	@cp libft/libft.a libft.a

clean:
	@echo "Temp files cleaning..."
	@rm -f $(OBJECTS)
	@echo "Temp files cleaning done !\n"

fclean:
	@echo "Cleaning all..."
	@make fclean -C libft
	@rm -f $(NAME) $(OBJECTS) $(LIB)
	@echo "Cleaning done !\n"

display:
	@echo "^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^\n"

usage:
	@echo "Usage: ./pipex <infile> \"<shell command>\" \"<shell command>\" <outfile>\n"

re: fclean all

.PHONY: all clean fclean re display
