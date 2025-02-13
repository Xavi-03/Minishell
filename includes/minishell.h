#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h> //idk if this is used
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>//debug
# include <signal.h> // for history
# define SINGLE_REDIR 1
# define DOUBLE_REDIR 2
# define NO_REDIR 0
# define RESET_COLOR "\033[0m"

typedef struct	s_sh
{
	int				last_command;
	char			**env;
	struct s_var	*var_list;
	struct s_cmd	*cmd_list;
	struct s_galloc	*l_galloc;
	char			**input_arr;
	char			*line;
}	t_sh;

typedef struct	s_cmd
{
	int				pid;
	int				not_found;
	int				main_process;
	int				cmd_count;
	int				out_pipe;
	int				in_pipe;
	int				*fd_pipe;
	int				f_next_infile;
	int				fd_in;
	int				fd_in_red;
	char			*infile;
	int				f_next_outfile;
	int				fd_out;
	int				fd_out_red;
	char			*outfile;
	int				built_in;
	char			**cmd_arr;
	struct s_cmd	*next;
	struct s_cmd	*start;
}	t_cmd;

typedef struct	s_var
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

typedef struct s_cmd_arr_args
{
	char	*str;
	char	**cmd_arr;
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	n_substr;
	/* data */
}				t_cmd_arr_args;

char	*get_next_line(int fd);
//55 f 6 s 1 m

//./buil_ins										FOLDER
//	built_in.c										FILE
//is_built_in    STATIC
//set_main_process    STATIC
void	find_built_in(char *input, t_sh *sh);
int		exec_built_in(t_sh *sh);
void	echo(t_sh *sh);
//	dir_builtins.c									FILE
void	cd(t_sh *sh);
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

//./execute											FOLDER
//	execute.c										FILE
void	subprocess_executer(t_sh *sh);
void	main_process_executer(t_sh *sh);
void	execute(t_sh *sh);
//	execute_utils.c									FILE
void	in_file(t_sh *sh);
void	out_file(t_sh *sh);
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
char	*arr_to_str(char **arr);
t_sh	*init_sh(char **env);
void	prompt_main(t_sh *sh);
//int	main(int argc, char **argv, char **env)		MAIN

//./parser											FOLDER
//	arr_utils.c										FILE
void	free_str_arr(char **str_arr);
//	parser.c										FILE
int		command_builder(char *input, t_sh *sh);
int		manage_cmd_pipes(t_sh *sh);
int		cmd_parser(char *input, t_sh *sh);
void	find_cmd(char **input_arr, t_sh *sh);
void	parser(t_sh *sh);
//	parser_utils.c									FILE
void	parse_file_redir(char *input, t_sh *sh);
void	check_in_out_file(char *input, t_sh *sh);
int		check_std_redir(char *input, t_sh *sh);
//	path_utils.c									FILE
char	*get_curr_dir(void);
//pathfinder    STATIC
char	*get_path(char *command);

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

//./variable_linked_list							FOLDER
//	var_utils.c										FILE
void	add_var(char *input, t_sh *sh);
char	**found_var(char *input, t_sh *sh);
void	var_delnode(char *var_name, t_sh *sh);
t_var	*var_addnode(t_sh *sh);
t_var	*var_init(t_var *var_node, t_sh *sh);

// ./cmd_arr
//cmd_arr stuff
int		get_n_cmds(char *str);
char	**prepare_cmd_arr(char *str, t_sh *sh);
void	process_redirs(t_cmd_arr_args *args, t_sh *sh);
void	process_everything_else(t_cmd_arr_args *args, t_sh *sh);
void	process_double_quotes(t_cmd_arr_args *args, t_sh *sh);
void	process_single_quotes(t_cmd_arr_args *args, t_sh *sh);
void	skip_escaped(t_cmd_arr_args *args, t_sh *sh);
char	*extract_between_chars(char *str, char c, t_sh *sh);
bool	is_in_set(char c, char *set);
char	**create_cmd_arr(char **cmd_arr, size_t n_substr, t_sh *sh);
void	cmd_arr_args_init(t_cmd_arr_args *args, char *str);
void	remove_backslashes(t_cmd_arr_args *args, t_sh *sh);
#endif

//valgrind --track-origins=yes --trace-children=yes --leak-check=full
// for check memory leaks with subprocess

/* DUDAS
Como reconocer commandos, y < > | u otros simbolos y no confundirlos con commandos,
entiendo que "< infile cmd1 | cm2 > outfile" infile se reconoce por que le precede
< pero no conozco todas las posibilidades ni como de lioso se pues poner

"infile < ls" mal
"< infile cat" bien




COSAS a revisar
Cuanto el ENV falla, debemos buscar una alternativa por ejemplo "unseth PATH"

*/


/*
//utils.c
//line_finder.c
char	*user_finder(char *user, char *pc, t_sh *sh);
char	*path_finder(t_sh *sh);
char	*prompt_finder(t_sh *sh);
char	*get_path(char *command);
//prompte_utils.c
int		ft_lentoc(const char *str, char c);
char	*promptjoin(char *user, char *path, t_sh *sh);
char	*userjoin(char *user, char *pc, t_sh *sh);
//galloc.c
void	gfree(void *ptr, t_sh *sh);
void	terminate(t_sh *sh);
void	free_galloc(t_sh *sh);
void	*add_galloc(void *mem, t_sh *sh);
void	*galloc(size_t size, t_sh *sh);
//parser.c
void	find_cmd(char **input_arr, t_sh *sh);
void	parser(t_sh *sh);
void	pipe_cleaner(t_sh *sh);
//execute.h
void	in_file(t_sh *sh);
void	out_file(t_sh *sh);
void	prepare_pipe(t_sh *sh);
t_cmd	*fork_create(t_sh *sh);
void	execute(t_sh *sh);
//built_ins.c
int		exec_built_in(t_sh *sh);
void	find_built_in(char *input, t_sh *sh);
void	cd(t_sh *sh);
void	echo(t_sh *sh);
void	export(t_sh *sh);
void	unset(t_sh *sh);
void	executer_built_in(t_sh *sh);
void	print_env(t_sh *sh);
//built_in_utils.c
char	**add_var_env(t_sh *sh);
char	**remove_var_env(char *var_name, t_sh *sh);
//cmd_utils.c
t_cmd	*cmd_addnode(t_sh *sh);
t_cmd	*cmd_init(t_cmd *cmd_list, t_sh *sh);
//var_utils.c
void	var_delnode(char *var_name, t_sh *sh);
//char	*add_var(char *input, int input_idx, t_sh *sh); // merge pol
void	add_var(char *input, t_sh *sh); // merge javi
char	**found_var(char *input, t_sh *sh);
t_var	*var_init(t_var *var, t_sh *sh);
t_var	*var_addnode(t_sh *sh);

// Misc utils
void	free_str_arr(char **str_arr);
char	*extract_between_chars(char *str, char c);
char	**prepare_cmd_arr(char *str);
char	*get_env_var(char **env, char *env_var);

// Pipe utils
void	pipe_cleaner(t_sh *sh);

void	main_process_executer(t_sh *sh);
*/
