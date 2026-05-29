/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:31:41 by srichard          #+#    #+#             */
/*   Updated: 2026/05/25 02:54:13 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

// Includes system
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
// Readline
# include <readline/history.h>
# include <readline/readline.h>
// Libft
# include "../libft/libft.h"

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_L_PAREN,
	TOKEN_R_PAREN
}								t_token_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}								t_node_type;

/*Lexer (tokens)*/
typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

/*Parser*/
typedef struct s_ast_node
{
	t_node_type					type;
	char						**args;
	t_token						*redirections;
	struct s_ast_node			*left;
	struct s_ast_node			*right;
}								t_ast_node;

/*Env*/
typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

/*Global stat struct minishell*/
typedef struct s_minishell
{
	t_env						*env_list;
	int							last_exit_status;
	int							is_running;
	char						**env_array;
	t_token						*tokens;
	t_ast_node					*ast;
	char						**heredoc_tmpfiles;
	int							in_pipe;
}								t_minishell;

/*Stock the last signal received*/
extern volatile sig_atomic_t	g_signal;

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

void							process_ast(t_minishell *shell);
// Utils
int								is_space(char c);
int								is_operator(char *str);
int								get_word_len(char *str);
int								check_unclosed_quotes(char *input);
int								ft_strcmp(const char *s1, const char *s2);

// Free
void							free_tokens(t_token *tokens);
void							free_env(t_env *env_list);
void							free_ast(t_ast_node *node);
void							free_string_array(char **arr);
void							free_all_and_exit(t_minishell *shell,
									int exit_code);

// Parser
int								count_args(t_token *tokens);
t_ast_node						*parse_command(t_token **tokens);
int								handle_redirection(t_ast_node *node,
									t_token **tokens);
t_ast_node						*parse_pipeline(t_token **tokens);
t_ast_node						*parse_logical(t_token **tokens);
t_ast_node						*parse_primary(t_token **tokens);
t_ast_node						*syntax_error_node(t_token *token);

// Utils token
t_token							*create_token(t_token_type type, char *value);
void							add_token(t_token **tokens, t_token *new_node);
int								check_syntax_subshell(t_token *tokens);

// Lexer
t_token							*lexer(char *input, t_minishell *shell);
t_token							*extract_word(char *input, int *i);
t_token							*extract_operator(char *input, int *i);

// Environnement
t_env							*create_env_node(char *key, char *value);
void							add_env_node(t_env **env_list, t_env *new_node);
t_env							*init_env(char **envp);

// Wildcard
int								strcasecmp_custom(char *a, char *b);
int								match_pattern(char *pattern, char *word);
char							**get_wildcard_matches(char *pattern);
// Expander
char							*expand_word(char *word, t_minishell *shell);
void							expander(t_minishell *shell);
char							*get_shell_pid(void);
char							*handle_dollar(char *word, int *i,
									char *new_word, t_minishell *shell);
int								word_has_quotes(char *word);
t_token							*split_on_spaces(t_token *tmp, char *expanded,
									char *orig);

// Utils expander
char							*get_env_value(t_env *env_list, char *key);
char							*append_char(char *str, char c);
char							*append_str(char *s1, char *s2);
int								is_env_char(char c);

// Parser utils
t_ast_node						*create_command_node(void);
t_ast_node						*create_operator_node(t_node_type type,
									t_ast_node *left, t_ast_node *right);
int								is_redirection(t_token_type type);
int								is_controle_operator(t_token_type type);
t_ast_node						*create_subshell_node(t_ast_node *child);

// Env utils
int								is_valid_env_key(char *key);
char							*extract_key(char *arg);
char							*extract_value(char *arg);
t_env							*find_env_var(t_env *env_list, char *key);

// Export utils
void							print_export_error(char *arg);
void							sort_env(t_env **tab, int size);
void							display_and_free_tab(t_env **tab, int size);
void							print_sorted_env(t_minishell *shell);

// Built-ins
void							ft_echo(t_minishell *shell, char **args);
void							ft_cd(t_minishell *shell, char **args);
void							ft_pwd(t_minishell *shell, char **args);
void							ft_env(t_minishell *shell, char **args);
void							ft_export(t_minishell *shell, char **args);
void							ft_unset(t_minishell *shell, char **args);
void							ft_exit(t_minishell *shell, char **args);

// Builts-ins utils
void							update_or_create_env(t_minishell *shell,
									char *key, char *value, int append);
void							cd_error(t_minishell *shell, char *target);
int								is_valid_cd_args(char **args);
int								ft_exit_atoi(const char *s, long long *out);

// Signals
void							setup_sig_default(void);
void							setup_sig_prompt(void);
void							setup_sig_ignore(void);
void							setup_sig_heredoc(void);
void							setup_terminal_settings(void);
void							sigint_handler(int signal);

/* Execution */
// AST & Pipes
int								exec_ast(t_ast_node *node, t_minishell *shell);
void							exec_pipe(t_ast_node *node, t_minishell *shell);
int								fork_error(t_minishell *shell, int fd[2],
									pid_t launched_pid);
void							child_left(t_ast_node *node, t_minishell *shell,
									int fd[2]);
void							child_right(t_ast_node *node,
									t_minishell *shell, int fd[2]);

// Executor
void							exec(t_minishell *shell, char **args,
									t_token *redir_list, char **envp);
void							handle_child_status(t_minishell *shell,
									int status);
char							**env_list_to_array(t_env *env_list);
// Exec Utils
void							check_cmd_edge_cases(t_minishell *shell,
									char **args);
void							check_is_dir(t_minishell *shell, char *path);
void							handle_exec_error(t_minishell *shell,
									char *path, char **args);
// External Commands
void							exec_child(t_minishell *shell, char **args,
									t_token *redir_list, char **envp);
char							*get_cmd_path(t_env *env_list, char *cmd);

// Built-ins
int								is_builtin(char *cmd);
int								exec_builtin(t_minishell *shell, char **args);
void							exec_builtin_redir(t_minishell *shell,
									char **args, t_token *redir_list);

// Redirections
int								setup_redirections(t_minishell *shell,
									t_token *redir_list);
// Heredoc
int								heredoc(t_minishell *shell,
									t_token *redir_list);
void							write_heredoc_line(char *line, int fd_out);
char							*heredoc_prompt(void);
int								handle_parent_heredoc(pid_t pid, int fd[2]);
char							*clean_heredoc_delim(char *eol);
int								open_error(char *file);
int								handle_single_redir(t_token *tmp, char *file);
int								apply_redir_logic(t_minishell *shell,
									t_token *tmp, int orig_stdin);
int								apply_heredoc_pass(t_minishell *shell,
									t_token *tmp, int orig_stdin);
int								apply_file_pass(t_token *tmp);
int								handle_redir_pass(t_minishell *shell,
									t_token *redir_list, int orig_stdin,
									int heredoc_only);

// Heredoc Collect
void							collect_heredocs_ast(t_ast_node *node,
									t_minishell *shell);
void							collect_heredocs_from_redir(t_token *redir_list,
									t_minishell *shell);
int								get_unique_heredoc_fd(char **temp_path);

// Free utils
void							free_string_array(char **arr);
void							free_tokens(t_token *tokens);
void							remove_heredoc_tmpfiles(t_minishell *shell);

#endif
