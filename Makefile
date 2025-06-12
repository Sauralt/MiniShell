NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj
LIBFT_DIR = libft
LIBS = -lreadline
INCLUDE_DIR = Include

EXEC = 		srcs/exec/exec.c srcs/exec/heredoc.c srcs/exec/init_env.c \
			srcs/exec/meta_char.c srcs/exec/process.c srcs/exec/read_in_stdin.c \

FUNCTIONS =	srcs/functions/cd.c srcs/functions/echo.c srcs/functions/env.c \
			srcs/functions/exit.c srcs/functions/export.c srcs/functions/pwd.c \
			srcs/functions/unset.c

MAIN =		srcs/main/cmd_input.c srcs/main/main.c

PARSING =	srcs/parsing/dollar.c srcs/parsing/parsing.c srcs/parsing/init_types.c \
			srcs/parsing/meta_in_word.c srcs/parsing/remove_quotes.c \
			srcs/parsing/dollar_2.c srcs/parsing/change_str.c 

UTILS =		srcs/utils/env_functions.c srcs/utils/find.c srcs/utils/free.c \
			srcs/utils/random_utils.c srcs/utils/token_functions.c srcs/utils/last_norm.c \
			srcs/utils/random_utils_2.c srcs/utils/norm_functions.c \
			srcs/utils/builtins_norm.c srcs/utils/wait.c srcs/utils/builtins_norm_2.c

FT_DPRINTF = srcs/ft_dprintf/ft_dprintf.c srcs/ft_dprintf/ft_printhex.c srcs/ft_dprintf/ft_printint.c \
			srcs/ft_dprintf/ft_printptr.c srcs/ft_dprintf/ft_printstring.c srcs/ft_dprintf/ft_printuns.c

MINISHELL = $(EXEC) $(FUNCTIONS) $(MAIN) $(PARSING) $(UTILS) $(FT_DPRINTF)

OBJS = $(MINISHELL:srcs/%.c=obj/%.o)

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR) -I$(INCLUDE_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS)

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
