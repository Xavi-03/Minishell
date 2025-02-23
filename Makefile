CC		:= clang
NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror -g -fsanitize=address
LIBFT	:= ./lib/libft
INCLUDE	:= -I ./includes -I $(LIBFT)
HEADERS	:= ./includes/minishell.h \
./lib/libft/libft.h
LIBS	:= -L $(LIBFT) -lft -lreadline
SRCS	:= ./src/built_ins/built_in.c \
./src/built_ins/echo.c \
./src/built_ins/env_builtins.c \
./src/built_ins/dir_builtins.c \
./src/cmd_linked_list/cmd_utils.c \
./src/execute/execute.c \
./src/execute/execute_utils.c \
./src/galloc/init_galloc.c \
./src/galloc/galloc.c \
./src/minishell/main.c \
./src/parser/arr_utils.c \
./src/parser/parser_utils.c \
./src/parser/path_utils.c \
./src/parser/parser.c \
./src/variable_linked_list/var_nodes.c \
./src/variable_linked_list/var_utils.c \
./src/env/env_shlvl.c \
./src/env/env_backup.c \
./src/env/env_var_utils.c \
./src/prompt/prompt_finder.c \
./src/prompt/prompt_utils.c \
./src/heredoc/heredoc.c \
./src/token_arr/token_arr_utils.c \
./src/token_arr/token_double_quotes.c \
./src/token_arr/token_single_quotes.c \
./src/token_arr/token_everything_else.c \
./src/token_arr/token_redirs.c \
./src/misc/misc_utils.c \
./src/redir_linked_list/redir_prepare.c \
./src/redir_linked_list/redir_utils.c

OBJS	:= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@make -s -C $(LIBFT)

%.o: %.c $(HEADERS) $(LIBFT)/Makefile Makefile
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: clean all

.PHONY: all, clean, fclean, re
