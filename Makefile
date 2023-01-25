NAME = pipex
# BNS = pipex_bonus
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
SRC = pipex.c pipex_helper.c pipex_utils.c ft_putstr_fd.c ft_split.c error.c\
		get_next_line_bonus.c get_next_line_utils_bonus.c 
BONUS = pipex_bonus.c error.c pipex_helper_bonus.c pipex_utils_bonus.c ft_putstr_fd.c ft_split.c\
		get_next_line_bonus.c get_next_line_utils_bonus.c 

OSRC = ${SRC:.c=.o}
OBONUS = ${BONUS:.c=.o}

all: $(NAME)

$(NAME): $(OSRC)
	$(CC) $(CFLAGS) $(OSRC) -o $(NAME)

bonus: $(OBONUS)
	$(CC) $(CFLAGS) $(OBONUS) -o $(NAME)
clean:
	rm -f $(OSRC) $(OBONUS)
fclean: clean
	rm -f $(NAME)
re: fclean all