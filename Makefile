# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lupalhan <lupalhan@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/17 19:03:03 by lupalhan          #+#    #+#              #
#    Updated: 2025/10/24 18:06:03 by lupalhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cc = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ./ft_isdigit.c \
       ./ft_isalpha.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
