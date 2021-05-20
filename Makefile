# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 19:41:16 by mhaddi            #+#    #+#              #
#    Updated: 2021/05/20 19:59:05 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = clang
FLAGS = -Wall -Wextra -Werror
DFLAGS = -g -fsanitize=address
SRCS = $(find ./src/. -name '*.c')
MLX = ./mlx/libmlx.a

all: $(NAME)

$(MLX):
	$(MAKE) -C ./mlx/
	cp $(MLX)

$(NAME): $(SRCS)
	make -C ./mlx/
	CC $(DFLAGS) -c $(SRCS) -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	# make -C ./libft/
	# make -C ./parser/
	# CC $(SRCS) -g -L ./libft -lft -L ./parser -lparser -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make -C ./mlx/ clean
	# make -C ./parser/ clean
	# make -C ./libft/ clean

fclean:
	make -C ./mlx/ clean
	rm cub3d
	# make -C ./parser/ fclean
	# make -C ./libft/ fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
