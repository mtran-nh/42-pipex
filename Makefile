# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 16:57:29 by mtran-nh          #+#    #+#              #
#    Updated: 2025/09/23 19:05:05 by mtran-nh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft
LIBFT = Libft/libft.a

SRCS = src/path.c \
       src/utils.c \
       src/exec.c \
       src/main.c \
	   src/split.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = bonus_src/path_bonus.c \
             bonus_src/utils_bonus.c \
			 bonus_src/gnl.c \
			 bonus_src/split_bonus.c \
			 bonus_src/exec_bonus.c \
             bonus_src/main_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(BONUS)
$(BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS)

$(LIBFT):
	$(MAKE) -C Libft

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C Libft clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C Libft fclean

re: fclean all

.PHONY: all clean fclean re
