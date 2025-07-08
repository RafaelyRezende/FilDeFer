CC = cc

NAME =fdf

MAIN_SRC =srcs/render.c srcs/ft_put_pixel.c 

LIBFT =libft/libft.a

all: $(NAME)

$(NAME): $(MAIN_SRC)
	$(CC) $(MAIN_SRC) $(LIBFT) -g -Iinclude -Ilibft -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

srcs/%.o: srcs/%.c
	$(CC) -g $(CFLAGS) -o $@ -c $<

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
