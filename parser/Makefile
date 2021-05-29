# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 17:11:07 by mhaddi            #+#    #+#              #
#    Updated: 2021/05/29 13:29:57 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
DFLAGS = -g -g3 -fsanitize=address
CC = gcc
SRCS =	src/get_next_line.c \
		src/get_next_line_utils.c \
		src/parse_map.c \
		src/save_color.c \
		src/check_element.c \
		src/parse_file.c \
		src/save_texture.c \
		src/save_player.c \
		src/free_memory.c \
		src/ft_error.c \
		src/map_error.c \
		src/map_error_utils.c
NAME = libparser.a

all: $(NAME)

$(NAME): $(SRCS) ./Makefile
	gcc $(FLAGS) $(SRCS) -c
	ar rc $(NAME) *.o

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
