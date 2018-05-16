# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/11 15:56:03 by obamzuro          #+#    #+#              #
#    Updated: 2018/05/16 13:31:06 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCNAME = main.c		\
		  msh_strjoin.c	

FLAGS = -Wall -Wextra -Werror

SRC = $(addprefix source/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

HDRDIR = include

HDR = include/minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	gcc -g -I $(HDRDIR) $(OBJ) -L libft -lft -L ftprintf -lftprintf -o $(NAME)

%.o: %.c $(HDR)
	gcc -g -I $(HDRDIR) -c $< -o $@

clean:
	find . -name "*.o" -exec rm -rf {} \;

fclean: clean
	rm -rf $(NAME)

re: fclean all
