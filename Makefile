CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude -Ilibft -Iminilibx-linux -Lminilibx-linux -lmlx_Linux -L/usr/lib  -lXext -lX11 -lm -lz

CDB = -g -pg

OPTFLAGS = -O3 -flto -fstrict-aliasing -ffast-math ##-march=native -funroll-loops

## FDF

NAME = fdf

MLX = minilibx-linux/libmlx.a

MAIN_SRC = srcs/colors.c srcs/colors_utils.c srcs/ga_utils.c srcs/quaternion.c srcs/quaternion_utils.c srcs/rotation.c srcs/garbage_collection.c srcs/sort.c srcs/render.c srcs/line_utils.c srcs/parser.c srcs/parser_utils.c srcs/events.c srcs/unit_tester.c

OBJS = $(MAIN_SRC:.c=.o)

## Test executable names 

UNIT_TEST = unit_test

## Test srcs

UNIT_SRCS= $(MAIN_SRC)

## Includes
LIBFT =libft/libft.a

all: $(NAME)

test: $(PARSER_TEST)

$(UNIT_TEST): $(LIBFT) $(MLX) $(UNIT_SRCS)
	$(CC) $(OPTFLAGS) $(UNIT_SRCS) $(LIBFT) $(CFLAGS) -o $@

$(NAME): $(LIBFT) $(MLX) $(MAIN_SRC)
	$(CC) $(OPTFLAGS) $(MAIN_SRC) $(LIBFT) $(CFLAGS) -o $(NAME)

srcs/%.o: srcs/%.c
	$(CC) -g $(CFLAGS) -o $@ -c $<

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx-linux/

clean:
	@rm -rf $(OBJS)
	$(MAKE) clean -C libft 
	$(MAKE) clean -C minilibx-linux

fclean: clean
	$(MAKE) -C libft fclean
	@rm $(NAME)
re: fclean all

.PHONY: clean fclean re all unit_test
