# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 16:57:29 by mtran-nh          #+#    #+#              #
#    Updated: 2025/09/13 19:26:03 by mtran-nh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft
LIBFT = Libft/libft.a

SRCS = src/path.c \
       src/utils.c \
       src/exec.c \
       src/main.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C Libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C Libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C Libft fclean

re: fclean all

.PHONY: all clean fclean re
