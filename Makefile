CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude -Ilibft -Iminilibx-linux -Lminilibx-linux -lmlx_Linux -L/usr/lib  -lXext -lX11 -lm -lz

CDB = -g -pg

OPTFLAGS = -O3 -flto -fstrict-aliasing -ffast-math ##-march=native -funroll-loops

## FDF

NAME = fdf

MAIN_SRC = srcs/garbage_collection.c srcs/sort.c srcs/render.c srcs/line_utils.c srcs/parser.c srcs/transforms2.c  srcs/events.c srcs/unit_tester.c

OBJS = $(MAIN_SRC:.c=.o)

## Test executable names 

PARSER_TEST = parser_test

TRANS_TEST = tester_trans

UNIT_TEST = unit_test

## Test srcs

PARSER_SRCS= srcs/parser.c srcs/parser_main.c

TRANS_SRCS = srcs/transforms.c srcs/tester_transforms.c

UNIT_SRCS= srcs/garbage_collection.c srcs/sort.c srcs/render.c srcs/line_utils.c srcs/parser.c srcs/transforms2.c srcs/events.c srcs/unit_tester.c

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
	$(CC) $(OPTFLAGS) $(UNIT_SRCS) $(LIBFT) $(CFLAGS) -o $@

$(NAME): $(LIBFT) $(MAIN_SRC)
	$(CC) $(OPTFLAGS) $(MAIN_SRC) $(LIBFT) $(CFLAGS) -o $(NAME)

srcs/%.o: srcs/%.c
	$(CC) -g $(CFLAGS) -o $@ -c $<

$(LIBFT):
	make -C libft

clean:
	@rm -rf $(PARSER_TEST)
	@rm -rf $(NAME)
	@rm -rf $(TRANS_TEST)
	@rm -rf $(UNIT_TEST)
	@rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	make -C libft fclean

re: fclean all

.PHONY: clean fclean re all test trans unit
