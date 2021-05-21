# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/05/21 21:57:58 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(shell find ./src -name '*.c')
OBJS		= $(SRCS:.c=.o)
CC			= clang
RM			= rm -f
CFLAGS		= -O3 -Wall -Wextra -Werror -I.
DFLAGS		= -g -fsanitize=address
LDFLAGS		= -L ./mlx/ -lmlx -L ./libft/ -lft -L ./parser/ -lparser -framework OpenGL -framework AppKit
MLX			= libmlx.a
LFT			= libft.a
PRS			= libparser.a
NAME		= cub3d

all:		$(NAME)

$(MLX):
			$(MAKE) -C ./mlx/

$(LFT):
			$(MAKE) -C ./libft/

$(PRS):
			$(MAKE) -C ./parser/

$(NAME):	$(MLX) $(LFT) $(PRS) $(OBJS)
			$(CC) $(DFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
			$(MAKE) -C ./mlx/ clean
			$(MAKE) -C ./libft/ clean
			$(MAKE) -C ./parser/ clean
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) -C ./libft/ fclean
			$(MAKE) -C ./parser/ fclean
			$(RM) $(NAME) $(MLX)

re:			fclean all

.PHONY:		all clean fclean re
