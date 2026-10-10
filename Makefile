## FDF — SDL2/WebAssembly Makefile (minilibx fully removed)
##
## Targets:
##   all       native Linux binary `fdf` (SDL2 + SDL2_ttf via pkg-config,
##             fallback sdl2-config)
##   testhook  native binary `fdf_testhook` built with -DFDF_TEST_HOOK
##             (headless smoke test: FDF_HEADLESS_FRAMES=N frames then quit)
##   wasm      Emscripten build -> web/fdf.{html,js,wasm,data}
##   clean / fclean / re
##
## Native and wasm objects are kept in separate trees (build/native and
## build/wasm) so the two toolchains never clash. libft accepts a CC
## override (`make -C libft CC=emcc`) and an OBJDIR/NAME redirect.

NAME		= fdf
TESTHOOK	= fdf_testhook

CC			= cc
EMCC		= emcc

# -std=gnu89 kept: SDL2 headers compile cleanly with it under gcc/clang.
CFLAGS		= -Wall -Werror -Wextra -O3 -flto -fstrict-aliasing -ffast-math -std=gnu89
SDL_CFLAGS	:= $(shell pkg-config --cflags sdl2 SDL2_ttf 2>/dev/null || sdl2-config --cflags)
SDL_LIBS	:= $(shell pkg-config --libs sdl2 SDL2_ttf 2>/dev/null || \
				  (sdl2-config --libs && echo -lSDL2_ttf))
INCLUDES	= -Iinclude -Ilibft $(SDL_CFLAGS)
LDLIBS		= $(SDL_LIBS) -lm

# wasm: -O2, no -ffast-math/-flto (documented choice: -ffast-math breaks
# NaN/Inf semantics that the quaternion path relies on; LTO off to keep
# emscripten port flags consistent across objects).
WASM_CFLAGS	= -Wall -Werror -Wextra -O2 -std=gnu89
WASM_SDL	= -sUSE_SDL=2 -sUSE_SDL_TTF=2
WASM_FLAGS	= $(WASM_SDL) -sALLOW_MEMORY_GROWTH=1 \
			  --preload-file maps@/maps --preload-file assets@/assets \
			  --shell-file web/shell.html -O2
WASM_OUT	= web/fdf.html

SRC_DIR		= srcs
SRCS		= $(addprefix $(SRC_DIR)/, \
			  main.c \
			  platform.c font.c \
			  parser.c parser_utils.c \
			  ga_utils.c quaternion.c quaternion_utils.c \
			  rotation.c render.c line_utils.c sort.c \
			  colors.c colors_utils.c \
			  events.c garbage_collection.c)

BUILD_NATIVE	= build/native
BUILD_WASM		= build/wasm
OBJS			= $(patsubst $(SRC_DIR)/%.c,$(BUILD_NATIVE)/%.o,$(SRCS))
DEPS			= $(OBJS:.o=.d)
HOOK_OBJS		= $(patsubst $(SRC_DIR)/%.c,$(BUILD_NATIVE)/hook/%.o,$(SRCS))
HOOK_DEPS		= $(HOOK_OBJS:.o=.d)
WASM_OBJS		= $(patsubst $(SRC_DIR)/%.c,$(BUILD_WASM)/%.o,$(SRCS))

LIBFT			= libft/libft.a
WASM_LIBFT		= $(BUILD_WASM)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)

$(BUILD_NATIVE)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft CC=$(CC)

testhook: $(TESTHOOK)

$(TESTHOOK): $(HOOK_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -DFDF_TEST_HOOK $(INCLUDES) $(HOOK_OBJS) $(LIBFT) $(LDLIBS) -o $(TESTHOOK)

$(BUILD_NATIVE)/hook/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DFDF_TEST_HOOK $(INCLUDES) -MMD -MP -c $< -o $@

wasm: $(WASM_OUT)

$(WASM_OUT): $(WASM_OBJS) $(WASM_LIBFT) web/shell.html assets/DejaVuSans.ttf maps/valid.fdf maps/pyramid.fdf
	$(EMCC) $(WASM_CFLAGS) $(WASM_OBJS) $(WASM_LIBFT) -lm $(WASM_FLAGS) -o $(WASM_OUT)

$(BUILD_WASM)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(EMCC) $(WASM_CFLAGS) $(WASM_SDL) -Iinclude -Ilibft -MMD -MP -c $< -o $@

$(WASM_LIBFT):
	@mkdir -p $(BUILD_WASM)/libft
	$(MAKE) -C libft CC=$(EMCC) AR=emar OBJDIR=$(abspath $(BUILD_WASM)/libft) \
		NAME=$(abspath $(WASM_LIBFT))

clean:
	rm -rf build
	$(MAKE) clean -C libft

fclean: clean
	$(MAKE) fclean -C libft
	rm -rf $(NAME) $(TESTHOOK) web/fdf.html web/fdf.js web/fdf.wasm web/fdf.data

re: fclean all

-include $(DEPS) $(HOOK_DEPS)

.PHONY: all testhook wasm clean fclean re
