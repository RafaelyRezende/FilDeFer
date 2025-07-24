CC = cc

NAME =fdf

MAIN_SRC = srcs/render.c srcs/ft_put_pixel.c srcs/ft_init_line.c srcs/parser.c srcs/ft_swap.c srcs/main.c srcs/transforms.c

OBJS = $(MAIN_SRC:.c=.o)

PARSER_SRCS= srcs/parser.c srcs/parser_main.c

PARSER_TEST = parser_test

TRANS_TEST = tester_trans

TRANS_SRCS = srcs/transforms.c srcs/tester_transforms.c

LIBFT =libft/libft.a

all: $(NAME)

test: $(PARSER_TEST)

trans: $(TRANS_TEST)

$(PARSER_TEST): $(LIBFT) $(PARSER_SRCS)
	$(CC) $(PARSER_SRCS) $(LIBFT) -g -pg -O3 -Iinclude -Ilibft -Iminilibx-linux -Lminilibx-linux -lmlx_Linux -L/usr/lib  -lXext -lX11 -lm -lz -o $(PARSER_TEST)

$(TRANS_TEST): $(LIBFT) $(PARSER_SRCS)
	$(CC) $(TRANS_SRCS) $(LIBFT) -g -pg -O3 -Iinclude -Ilibft -Iminilibx-linux -Lminilibx-linux -lmlx_Linux -L/usr/lib  -lXext -lX11 -lm -lz -o $(TRANS_TEST)

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
