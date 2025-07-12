CC = cc

NAME =fdf

MAIN_SRC =srcs/render.c srcs/ft_put_pixel.c srcs/ft_init_line.c srcs/ft_parser.c srcs/ft_swap.c srcs/main.c

OBJS = $(MAIN_SRC:.c=.o)

LIBFT =libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(MAIN_SRC)
	$(CC) $(MAIN_SRC) $(LIBFT) -g -Iinclude -Ilibft -Iminilibx-linux -Lminilibx-linux -lmlx_Linux -L/usr/lib  -lXext -lX11 -lm -lz -o $(NAME)

srcs/%.o: srcs/%.c
	$(CC) -g $(CFLAGS) -o $@ -c $<

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	make -C libft fclean

re: fclean all

.PHONY: clean fclean re all
