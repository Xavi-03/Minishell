/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:04:37 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 21:45:15 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>
# define SINGLE_REDIR 1
# define DOUBLE_REDIR 2
# define NO_REDIR 0
# define RESET_COLOR "\033[0m"

typedef struct s_sh
{
	int				last_command;
	char			**env;
	struct s_var	*var_list;
	struct s_cmd	*cmd_list;
	struct s_galloc	*l_galloc;
	struct s_token	**token_arr;
	char			*line;
	bool			syntax_error;
}	t_sh;

typedef struct s_redir
{
	int				f_next_infile;
	int				fd_in;
	int				fd_in_red;
	int				*pipe_fd;
	int				pid;
	char			*infile;
	int				f_next_outfile;
	int				fd_out;
	int				fd_out_red;
	char			*outfile;
	struct s_redir	*next;
	struct s_redir	*start;
}	t_redir;

typedef struct s_cmd
{
	int				pid;
	int				not_found;
	int				main_process;
	int				cmd_count;
	int				out_pipe;
	int				in_pipe;
	int				*fd_pipe;
	int				built_in;
	char			**cmd_arr;
	int				toke_len;
	struct s_redir	*redir_list;
	struct s_cmd	*next;
	struct s_cmd	*start;
}	t_cmd;

typedef struct s_token
{
	char	*str;
	bool	is_redir;
	bool	is_variable;
	bool	is_in_quotes;
	bool	is_command;
}	t_token;

typedef struct s_var
{
	char			*var_name;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_galloc
{
	void			*mem;
	struct s_galloc	*next;
	struct s_galloc	*start;
}	t_galloc;

typedef struct s_token_arr_args
{
	char	*str;
	t_token	**token_arr;
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	n_tokens;
	size_t	arr_len;
	/* data */
}				t_token_arr_args;

char	*get_next_line(int fd);

//./buil_ins										FOLDER
//	built_in.c										FILE
//is_built_in    STATIC
//set_main_process    STATIC
void	find_built_in(char *input, t_sh *sh);
int		exec_built_in(t_sh *sh);
void	echo(t_sh *sh);
void	exit_builtin(t_sh *sh);
//	dir_builtins.c									FILE
void	cd(t_sh *sh);
void	pwd(t_sh *sh);
//	env_builtins.c									FILE
void	print_env(t_sh *sh);
void	export(t_sh *sh);
void	unset(t_sh *sh);

//./cmd_linked_list									FOLDER
//	cmd_utils.c										FILE
t_cmd	*cmd_init(t_cmd *cmd_list, t_sh *sh);
t_cmd	*cmd_addnode(t_sh *sh);

//./env												FOLDER
//	env_var_utils.c									FILE
//cmp_var_names    STATIC
//dup_modify_env    STATIC
char	**add_var_env(t_sh *sh);
char	**env_backup(t_sh *sh);
//var_in_env    STATIC
char	**remove_var_env(char *var_name, t_sh *sh);
//	env_var_utils2.c								FILE
char	*ft_get_env(char *env_var, t_sh *sh);

//./execute											FOLDER
//	execute.c										FILE
void	subprocess_executer(t_sh *sh);
void	main_process_executer(t_sh *sh);
void	execute(t_sh *sh);
//	execute_utils.c									FILE
//prepare_in_file	STATIC
//prepare_out_file	STATIC
void	prepare_file(int flag, t_sh *sh);
t_cmd	*fork_create(t_sh *sh);
void	prepare_pipe(t_sh *sh);
void	pipe_cleaner(t_sh *sh);

//./galloc											FOLDER
//	galloc.c										FILE
void	terminate(int exit_value, t_sh *sh);
void	free_galloc(t_sh *sh);
void	*add_galloc(void *mem, t_sh *sh);
void	gfree(void *ptr, t_sh *sh);
void	*galloc(size_t size, t_sh *sh);

//./minishell										FOLDER
//	main.c											FILE
void	sig_handler(int signum);
void	sigabrt_handler(int signal);
char	*arr_to_str(char **arr, t_sh *sh);
t_sh	*init_sh(char **env);
void	prompt_main(t_sh *sh);
//int	main(int argc, char **argv, char **env)		MAIN

//./parser											FOLDER
//	arr_utils.c										FILE
void	free_str_arr(char **str_arr);
//	parser.c										FILE
int		command_builder(char *input, t_sh *sh);
int		manage_cmd_pipes(t_sh *sh);
int		cmd_parser(t_token *token, t_sh *sh);
void	find_cmd(t_token **token_arr, t_sh *sh);
void	parser(t_sh *sh);
//	parser_utils.c									FILE
void	parse_file_redir(char *input, t_sh *sh);
void	check_in_out_file(char *input, t_sh *sh);
int		check_std_redir(char *input, t_sh *sh);
//	path_utils.c									FILE
char	*get_curr_dir(t_sh *sh);
//pathfinder    STATIC
char	*get_path(char *command, t_sh *sh);

//./prompt											FOLDER
//	prompt_finder.c									FILE
char	*user_finder(char *user, char *pc, t_sh *sh);
char	*path_finder(t_sh *sh);
char	*prompt_finder(t_sh *sh);
//	promp_utils.c									FILE
void	join_prompt_val(char **prompt, char **val);
char	*promptjoin(char *user, char *path, t_sh *sh);
char	*userjoin(char *user, char *pc, t_sh *sh);
int		ft_lentoc(const char *str, char c);

//./redir_linked_list								FOLDER
//	redir_utils.c									FILE
t_redir	*redir_addnode(t_sh *sh);
t_redir	*redir_init(t_redir *redir_node, t_sh *sh);
int		check_redirs(t_sh *sh);

//./variable_linked_list							FOLDER
//	var_utils.c										FILE
void	add_var(char *input, t_sh *sh);
t_token	**found_var(char *input, t_sh *sh);
void	var_delnode(char *var_name, t_sh *sh);
t_var	*var_addnode(t_sh *sh);
t_var	*var_init(t_var *var_node, t_sh *sh);
char	*get_value(t_var *var_iter, char *input, t_sh *sh);

// ./cmd_arr
//cmd_arr stuff
int		get_n_cmds(char *str);
t_token	**prepare_token_arr(char *str, t_sh *sh);
void	process_redirs(t_token_arr_args *args, t_sh *sh);
void	process_everything_else(t_token_arr_args *args, t_sh *sh);
void	process_double_quotes(t_token_arr_args *args, t_sh *sh);
void	process_single_quotes(t_token_arr_args *args, t_sh *sh);
void	skip_escaped(t_token_arr_args *args, t_sh *sh);
char	*extract_between_chars(char *str, char c, t_sh *sh);
bool	is_in_set(char c, char *set);
t_token	**create_token_arr(t_token **token_arr, size_t n_tokens, t_sh *sh);
void	token_arr_args_init(t_token_arr_args *args, char *str);
void	remove_backslashes(t_token_arr_args *args, t_sh *sh);

// ./heredoc
void	heredoc(t_redir *redir, t_sh *sh);

// ./misc
bool	is_number(char *str);
size_t	count_chars(char *str, char c);
int		count_tokens(t_token **token_arr);

void	increase_shlvl(char **env, t_sh *sh);
#endif
//valgrind --track-origins=yes --trace-children=yes --leak-check=full
