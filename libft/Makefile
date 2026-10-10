## libft Makefile (rewritten: review finding P-07)
##
## Fixes vs. previous version:
##  - per-file pattern rule replaces the "$(OBJS): $(SRCS)" construct that
##    recompiled every source for every single object;
##  - `bonus` now builds on top of the base archive properly.
## SDL2/WebAssembly port:
##  - CC is overridable (`make -C libft CC=emcc`) for the wasm toolchain;
##  - OBJDIR redirects objects (default: in-tree) so the wasm build can
##    keep its objects under build/wasm/ without clashing with native ones;
##  - NAME can be overridden to redirect the archive location.

CC			= cc
AR			?= ar
CFLAGS		= -Wall -Wextra -Werror
NAME		= libft.a
OBJDIR		?= .

SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			  ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			  ft_memmove.c ft_memset.c ft_putchar.c ft_putstr.c ft_strchr.c ft_strcmp.c \
			  ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			  ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			  ft_tolower.c ft_toupper.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			  ft_putstr_fd.c ft_itoa.c ft_split.c get_next_line.c get_next_line_utils.c \
			  ft_printf.c ft_printf_utils.c
OBJS		= $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

BONUS_SRCS	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			  ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c \
			  ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUS_OBJS	= $(addprefix $(OBJDIR)/,$(BONUS_SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
