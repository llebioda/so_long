CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCFILES = main.c map.c map_utils.c map_checker.c map_path_checker.c utils.c player.c enemy.c sprites.c renderer.c canvas_renderer.c ft_bzero.c ft_itoa.c ft_file_as_extension.c ft_substr.c
SRCDIR = ./
SRCS = $(addprefix $(SRCDIR), $(SRCFILES))
OBJDIR = ./build/
OBJS = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))

HEADERFILES = so_long.h
HEADERDIR = ./
HEADERS = $(addprefix $(HEADERDIR), $(HEADERFILES))
INCLUDES = -I $(HEADERDIR)

GETNEXTLINE_PATH = ./get_next_line
GETNEXTLINE_SRC = get_next_line.c get_next_line_utils.c
SRCS += $(addprefix $(GETNEXTLINE_PATH)/, $(GETNEXTLINE_SRC))
OBJS += $(addprefix $(GETNEXTLINE_PATH)/, $(GETNEXTLINE_SRC:.c=.o))
HEADERS += $(GETNEXTLINE_PATH)/get_next_line.h
INCLUDES += -I $(GETNEXTLINE_PATH)

MLX_PATH = ./minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11
INCLUDES += -I $(MLX_PATH)

NAME = so_long

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(MLX_LIB): $(MLX_PATH)
	@make -sC $(MLX_PATH)

$(MLX_PATH):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_PATH)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
