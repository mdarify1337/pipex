NAME = pipex

CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c pipex_helper.c pipex_utils.c error.c
BONUS = pipex_bonus.c error_bonus.c pipex_helper_bonus.c pipex_utils_bonus.c 
		
UTILS = get_next_line_bonus.c get_next_line_utils_bonus.c ft_putstr_fd.c ft_split.c

OUTILS = ${UTILS:.c=.o}
OSRC = ${SRC:.c=.o}
OBONUS = ${BONUS:.c=.o}

all: $(OSRC)

$(OSRC): $(OUTILS) $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	@rm -rf pipex_bonus.o
	$(CC) $(CFLAGS) $(OSRC) $(OUTILS) -o $(NAME)

bonus: $(OBONUS)

$(OBONUS) : $(OUTILS) $(BONUS)
	$(CC) $(CFLAGS) -c $(BONUS)
	@rm -rf pipex.o
	$(CC) $(CFLAGS) $(OBONUS) $(OUTILS) -o $(NAME)
clean:
	rm -f $(OSRC) $(OBONUS) $(OUTILS)
fclean: clean
	rm -f $(NAME)
re: fclean all