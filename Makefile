# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/05/25 05:16:23 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(shell find ./src -name '*.c')
CC			= clang
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g -fsanitize=address
LDFLAGS		= -L ./mlx/ -lmlx -L ./libft/ -lft -L ./parser/ -lparser -framework OpenGL -framework AppKit
MLX			= libmlx.a
LFT			= libft.a
PRS			= libparser.a
NAME		= cub3d

all:		$(NAME)

$(NAME):	$(MLX) $(LFT) $(PRS)
			$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(NAME)

$(MLX):
			$(MAKE) -C ./mlx/

$(LFT):
			$(MAKE) -C ./libft/

$(PRS):
			$(MAKE) -C ./parser/

clean:
			$(MAKE) -C ./mlx/ clean
			$(MAKE) -C ./libft/ clean
			$(MAKE) -C ./parser/ clean
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) -C ./libft/ fclean
			$(MAKE) -C ./parser/ fclean
			$(RM) $(NAME)
			$(RM) -rf $(NAME).dSYM
			$(RM) screenshot.bmp

re:			fclean all

.PHONY:		all clean fclean re
