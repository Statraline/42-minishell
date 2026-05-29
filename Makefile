NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
LDFLAGS = -L$(LIBFTDIR) -lft -lreadline
HEADER = includes/minishell.h

SRCS = srcs/main.c \
		srcs/main_utils.c\
		srcs/lexer/lexer.c\
		srcs/utils/utils.c\
		srcs/utils/free.c\
		srcs/lexer/token_utils.c\
		srcs/env/env.c\
		srcs/wildcard/wildcard.c\
		srcs/wildcard/wildcard_utils.c\
		srcs/expander/expander.c\
		srcs/expander/pid_utils.c\
		srcs/expander/expander_utils.c\
		srcs/expander/expander_utils2.c\
		srcs/parser/parser_utils.c\
		srcs/parser/parser.c\
		srcs/parser/parser2.c\
		srcs/builtins/env.c\
		srcs/builtins/env_utils.c\
		srcs/builtins/export.c\
		srcs/builtins/pwd.c\
		srcs/builtins/unset.c\
		srcs/builtins/cd.c\
		srcs/builtins/cd_utils.c\
		srcs/builtins/echo.c\
		srcs/builtins/exit.c\
		srcs/builtins/exit_utils.c\
		srcs/builtins/export_utils.c\
		srcs/exec/exec.c\
		srcs/exec/exec_builtin.c\
		srcs/exec/exec_cmd_ext.c\
		srcs/exec/exec_cmd_ext_utils.c\
		srcs/exec/pipes.c\
		srcs/exec/pipes_utils.c\
		srcs/exec/redirections.c \
		srcs/exec/redirections_utils.c \
		srcs/exec/heredoc.c \
		srcs/exec/heredoc_utils.c \
		srcs/exec/heredoc_collect.c \
		srcs/exec/heredoc_collect_utils.c \
		srcs/exec/signals.c \
		srcs/exec/signals_utils.c \
		srcs/utils/free_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HEADER) 
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFTDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re