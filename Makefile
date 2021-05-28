# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/05/28 16:11:02 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(shell find ./src -name '*.c')
CC			= clang
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g -fsanitize=address
LDLIBS		= -L ./mlx/ -lmlx -L ./libft/ -lft -L ./parser/ -lparser -framework OpenGL -framework AppKit
MLX			= mlx/libmlx.a
LFT			= libft/libft.a
PRS			= parser/libparser.a
NAME		= cub3D

all:		$(NAME)

$(NAME):	$(MLX) $(LFT) $(PRS)
			$(CC) $(CFLAGS) $(SRCS) $(LDLIBS) -o $(NAME)

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
			$(RM) -r *.dSYM
			$(RM) screenshot.bmp

re:			fclean all

.PHONY:		all clean fclean re
