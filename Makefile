SRCS		= $(shell find ./src/. -name '*.c')
OBJS		= $(SRCS:.c=.o)
CC			= clang
RM			= rm -f
CFLAGS		= -O3 -Wall -Wextra -Werror -I.
DFLAGS		= -g -fsanitize=address
LIBS		= -L ./mlx/ -lmlx -framework OpenGL -framework AppKit
MLX			= libmlx.a
NAME		= cub3d

all:		$(NAME)

$(NAME):	$(MLX) $(OBJS)
			$(CC) ${DFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
			@$(MAKE) -C ./mlx/

clean:
			@$(MAKE) -C ./mlx/ clean
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME) $(MLX)

re:			fclean all

.PHONY:		all clean fclean re
