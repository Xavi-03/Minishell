#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
}	t_sh;

typedef struct	s_cmd
{
	int				pid;
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
	char			*var;
	char			**value;
	struct s_var	*next;
}	t_var;

typedef struct s_galloc
{
	void			*mem;
	struct s_galloc	*next;
	struct s_galloc	*start;
}	t_galloc;

//utils.c

//line_finder.c
char	*user_finder(char *user, char *pc, t_sh *sh);
char	*path_finder(t_sh *sh);
char	*line_finder(t_sh *sh);
char	*get_path(char *command);
//linee_utils.c
int		ft_lentoc(const char *str, char c);
char	*linejoin(char *user, char *path, t_sh *sh);
char	*userjoin(char *user, char *pc, t_sh *sh);
//galloc.c
void	terminate(t_sh *sh);
void	free_galloc(t_sh *sh);
void	*add_galloc(void *mem, t_sh *sh);
void	*galloc(size_t size, t_sh *sh);
//parser.c
void	find_cmd(char **input_arr, t_sh *sh);
void	parser(char **input_arr, t_sh *sh);
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
void	executer_built_in(t_sh *sh);
//cmd_utils.c
t_cmd	*cmd_addnode(t_sh *sh);
t_cmd	*cmd_init(t_cmd *cmd_list, t_sh *sh);
//var_utils.c
void	add_var(char *input, t_sh *sh);
char	**found_var(char *input, t_sh *sh);
t_var	*var_init(t_var *var, t_sh *sh);
t_var	*var_addnode(t_sh *sh);

// Misc utils
void	free_str_arr(char **str_arr);

// Pipe utils
void	pipe_cleaner(t_sh *sh);

#endif
/* DUDAS
Como reconocer commandos, y < > | u otros simbolos y no confundirlos con commandos,
entiendo que "< infile cmd1 | cm2 > outfile" infile se reconoce por que le precede
< pero no conozco todas las posibilidades ni como de lioso se pues poner

"infile < ls" mal
"< infile cat" bien




COSAS a revisar
Cuanto el ENV falla, debemos buscar una alternativa por ejemplo "unseth PATH"

*/
