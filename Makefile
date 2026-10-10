## FDF — root Makefile (rewritten: review finding A-04)
##
## Fixes vs. previous version:
##  - compile flags (CFLAGS) and link libraries (LDLIBS) are separated;
##  - object files are compiled per-source with automatic header dependency
##    generation (-MMD -MP), so editing iso_fdf.h now triggers a rebuild;
##  - the minilibx prerequisite matches the linked artifact (libmlx_Linux.a);
##  - the broken `test` target (undefined PARSER_TEST) and the fake
##    `unit_test` binary (duplicate of fdf with the same main) are removed;
##  - fclean/.PHONY are consistent with the actual targets.

NAME		= fdf

CC			= cc
CDB			= -g
CFLAGS		= -Wall -Werror -Wextra -O3 -flto -fstrict-aliasing -ffast-math -std=gnu89
INCLUDES	= -Iinclude -Ilibft -Iminilibx-linux
LDLIBS		= -Lminilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRC_DIR		= srcs
SRCS		= $(addprefix $(SRC_DIR)/, \
			  main.c \
			  parser.c parser_utils.c \
			  ga_utils.c quaternion.c quaternion_utils.c \
			  rotation.c render.c line_utils.c sort.c \
			  colors.c colors_utils.c \
			  events.c garbage_collection.c)
OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)

LIBFT		= libft/libft.a
MLX			= minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CDB) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CDB) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx-linux

clean:
	rm -rf $(OBJS) $(DEPS)
	$(MAKE) clean -C libft
	$(MAKE) clean -C minilibx-linux

fclean: clean
	$(MAKE) fclean -C libft
	rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
