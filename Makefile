CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude -Ilibft -Iminilibx-linux -Lminilibx-linux -lmlx_Linux -L/usr/lib  -lXext -lX11 -lm -lz

CDB = -g -pg -O3

## FDF

NAME = fdf

MAIN_SRC = srcs/render.c srcs/ft_put_pixel.c srcs/ft_init_line.c srcs/parser.c srcs/ft_swap.c srcs/main.c srcs/transforms.c

OBJS = $(MAIN_SRC:.c=.o)

## Test executable names 

PARSER_TEST = parser_test

TRANS_TEST = tester_trans

UNIT_TEST = unit_test

## Test srcs

PARSER_SRCS= srcs/parser.c srcs/parser_main.c

TRANS_SRCS = srcs/transforms.c srcs/tester_transforms.c

UNIT_SRCS= srcs/render.c srcs/ft_swap.c srcs/ft_put_pixel.c srcs/ft_init_line.c srcs/parser.c srcs/transforms2.c srcs/events.c srcs/unit_tester.c

## Includes
LIBFT =libft/libft.a

all: $(NAME)

test: $(PARSER_TEST)

trans: $(TRANS_TEST)

unit: $(UNIT_TEST)

$(PARSER_TEST): $(LIBFT) $(PARSER_SRCS)
	$(CC) $(PARSER_SRCS) $(LIBFT) $(CFLAGS) -o $@

$(TRANS_TEST): $(LIBFT) $(PARSER_SRCS)
	$(CC) $(TRANS_SRCS) $(LIBFT) $(CFLAGS) -o $@

$(UNIT_TEST): $(LIBFT) $(UNIT_SRCS)
	$(CC) $(UNIT_SRCS) $(LIBFT) -std=c11 $(CFLAGS) -o $@

$(NAME): $(LIBFT) $(MAIN_SRC)
	$(CC) $(MAIN_SRC) $(LIBFT) -std=c11 $(CFLAGS) -o $(NAME)

srcs/%.o: srcs/%.c
	$(CC) -g $(CFLAGS) -o $@ -c $<

$(LIBFT):
	make -C libft

clean:
	@rm -rf $(PARSER_TEST)
	@rm -rf $(TRANS_TEST)
	@rm -rf $(UNIT_TEST)
	@rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	make -C libft fclean

re: fclean all

.PHONY: clean fclean re all test trans unit
