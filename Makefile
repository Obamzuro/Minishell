# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/11 15:56:03 by obamzuro          #+#    #+#              #
#    Updated: 2018/05/19 13:54:26 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCNAME = main.c		\
		  msh_strjoin.c	\
		  msh_strjoin_path.c\
		  msh_cd.c\
		  msh_echo.c\
		  msh_exec.c\
		  msh_exit.c\
		  msh_filler.c\
		  msh_free.c\
		  msh_get_printenv.c\
		  msh_print_pwd.c\
		  msh_setenv.c\
		  msh_signal_handler.c\
		  msh_unsetenv.c

FLAGS = -Wall -Wextra -Werror

SRC = $(addprefix source/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

HDRDIR = include

HDR = include/minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C ftprintf
	gcc -g -I $(HDRDIR) $(OBJ) -L libft -lft -L ftprintf -lftprintf -o $(NAME)

%.o: %.c $(HDR)
	gcc -g -I $(HDRDIR) -c $< -o $@

clean:
	make -C libft clean
	make -C ftprintf clean
	find . -name "*.o" -exec rm -rf {} \;

fclean: clean
	make -C libft fclean
	make -C ftprintf fclean
	rm -rf $(NAME)

re: fclean all
