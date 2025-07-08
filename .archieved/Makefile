CC = cc

ARC_LIB := ar rcs

CFLAGS := -Wall -Werror -Wextra -Imlx_linux -Iinclude -Ilibft -I/usr/include -o3

OFLAGS := -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

NAME =fdf

MAIN_SRC =srcs/render.c

SRCS =srcs/ft_put_pixel.c

OBJS =srcs/ft_put_pixel.o 

LIBFT =libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -Wall -Werror -Wextra -Iinclude -Ilibft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(MAIN_SRC) $(LIBFT) -o $(NAME)

srcs/%.o: srcs/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	make -C ./libft

clean:
	rm -rf srcs/$(OBJS)
	make clean -C ./libft

fclean: clean
	rm $(FDF_LIB)
	make fclean -C ./libft

re: fclean $(LIBFT)
	make

.PHONY: clean fclean re all
