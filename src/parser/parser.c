#include "../../includes/minishell.h"

int	command_builder(char *input, t_sh *sh)
{
	//char	*path;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	find_built_in(input, sh);
	if (sh->cmd_list->cmd_count == 0)
	{
		cmd->cmd_arr = galloc(10 * sizeof(char *), sh);
		if (cmd->built_in)
			cmd->cmd_arr[cmd->cmd_count] = ft_strdup(input);
		else
			cmd->cmd_arr[cmd->cmd_count] = get_path(input);
		add_galloc(cmd->cmd_arr[cmd->cmd_count], sh);
	}
	else
	{
		cmd->cmd_arr[cmd->cmd_count] = ft_strdup(input);
		add_galloc(cmd->cmd_arr[cmd->cmd_count], sh);
	}
	cmd->cmd_count += 1;
	cmd->cmd_arr[cmd->cmd_count] = NULL;
	return (0);
}

void	parse_file_redir(char *input, t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (cmd->f_next_infile > 0)
	{
		if (cmd->f_next_infile == DOUBLE_REDIR)
			cmd->fd_in_red = 1;
		cmd->f_next_infile = 0;
		cmd->infile = ft_strdup(input);
		add_galloc(cmd->infile, sh);
	}
	else if (cmd->f_next_outfile > 0)
	{
		if (cmd->f_next_outfile == DOUBLE_REDIR)
			cmd->fd_out_red = 1;
		cmd->f_next_outfile = 0;
		cmd->outfile = ft_strdup(input);
		add_galloc(cmd->outfile, sh);
	}
}

void	check_in_out_file(char *input, t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (ft_strncmp(input, "<", 2) == 0)
		cmd->f_next_infile = SINGLE_REDIR;
	else if (ft_strncmp(input, "<<", 3) == 0)
		cmd->f_next_infile = DOUBLE_REDIR;
	else if (ft_strncmp(input, ">", 2) == 0)
		cmd->f_next_outfile = SINGLE_REDIR;
	else if (ft_strncmp(input, ">>", 3) == 0)
		cmd->f_next_outfile = DOUBLE_REDIR;
	else
		parse_file_redir(input, sh);
}

int	check_std_redir(char *input, t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (ft_strncmp(input, ">", 2) == 0 || ft_strncmp(input, "<", 2) == 0 \
		|| ft_strncmp(input, ">>", 3) == 0 || ft_strncmp(input, "<<", 3) == 0 \
		|| cmd->f_next_infile > 0 || cmd->f_next_outfile > 0)
		return (1);
	return (0);
}

// he borrado char *input del input de la function
int	manage_cmd_pipes(t_sh *sh)
{
	t_cmd	*cmd;

	int		fd_pipe[2];
	cmd = sh->cmd_list;
	cmd->out_pipe = 1;
	cmd_addnode(sh);
	cmd = sh->cmd_list;
	if (pipe(fd_pipe) < 0) //TODO:hay que revisar si esto falla que hay que hacer
		printf("error\n");
	cmd->in_pipe = 1;
	cmd->fd_pipe = galloc(2 * sizeof(int), sh);
	cmd->fd_pipe[0] = fd_pipe[0];
	cmd->fd_pipe[1] = fd_pipe[1];
	return (1);
}

//command compare
//int	cmd_parser(char *input, int input_idx, t_sh *sh)
int	cmd_parser(char *input, t_sh *sh)
{
	t_cmd	*cmd;

	/*if(add_var(input, input_idx, sh)) // pol code in merge
		return (1);*/
	//else if (check_std_redir(input, sh))
	cmd = sh->cmd_list;
	//else if (check_std_redir(input, sh))
	if (ft_strchr(input, '='))//&& ft_strncmp(sh->cmd_list->cmd_arr[0], "export", ft_strlen("export")) != 0)
		add_var(input, sh);
	if (check_std_redir(input, sh))
		check_in_out_file(input, sh);
	else if (ft_strncmp(input, "|", 2) == 0)
		manage_cmd_pipes(sh);
	else
		command_builder(input, sh);
	return (0);
}

void	find_cmd(char **input_arr, t_sh *sh)
{
	static int	i = -1;

	char **var_arr;

	add_galloc(input_arr, sh);
	while (input_arr[++i])
	{
		add_galloc(input_arr[i], sh);
		if (!ft_strchr(input_arr[i], '$'))
		{
			cmd_parser(input_arr[i], sh); // necesita cambiar el nombre de funcion
			continue ;
		}
		var_arr = found_var(input_arr[i], sh);
		while (*var_arr)
		{
			cmd_parser(*var_arr, sh);
			var_arr++;
		}
	}
	if (!input_arr[i])
		i = -1;
}

/*void	find_cmd(char **input_arr, t_sh *sh)
{
	static int	i = -1;
	char	*value_var;
	//i = -1;
	add_galloc(input_arr, sh);
	while (input_arr[++i])
	{
		add_galloc(input_arr[i], sh);
		cmd_parser(input_arr[i], i, sh);
	}
	if (!input_arr[i])
		i = -1;
}*/

void	pipe_cleaner(t_sh *sh)
{
	t_cmd	*cmd_node;

	cmd_node = sh->cmd_list->start;
	while (cmd_node)
	{
		if (cmd_node->fd_pipe)
		{
			close(cmd_node->fd_pipe[0]);
			close(cmd_node->fd_pipe[1]);
		}
		cmd_node = cmd_node->next;
	}
}

/*
char *input_cleaner(char *input, t_sh *sh)
{
	char	*input_clean;
	int		i;
	int		need_space;
	int 	j;

	need_space = 0;
	i = -1;
	j = 0;
	while(input[++i])
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			if (i > 0 && input[i - 1] != ' ' && input[i - 1] != input[i])
				need_space += 1;
			if (input[i + 1] && input[i + 1] != ' ' && input[i + 1] != input[i])
				need_space += 1;
		}
	}
	input_clean = galloc((i + need_space + 1) * sizeof(char), sh);
	i = -1;
	while(input[++i])
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			if (i > 0 && input[i - 1] != ' ' && input[i - 1] != input[i])
				input_clean[j] = ' ';
			if (input[i + 1] && input[i + 1] != ' ' && input[i + 1] != input[i])
				input_clean[j] = ' ';
		}
		input_clean[j++] = input[i];
	}
	input_clean[j] = '\0';
	printf("%s\n");
	return (input);
}
*/
void	parser(t_sh *sh)
{
	//char **input_arr;
	t_cmd	*temp_cmd;
	char	**input_arr;
	 // var init
	sh->cmd_list = cmd_init(sh->cmd_list, sh);
	sh->cmd_list->start = sh->cmd_list;
	input_arr = sh->input_arr;

	find_cmd(input_arr, sh);
	if (!sh->cmd_list->cmd_arr)
		return ;
	if (sh->cmd_list->built_in || sh->cmd_list->cmd_arr)
		sh->cmd_list = fork_create(sh);
	// Subprocess
	if (sh->cmd_list->pid == -1 && !sh->cmd_list->main_process)
	{
		printf("Fork Error\n");
		exit(1); // TODO revisar si debe ser terminate o exit para el subproceso
	}
	else if (sh->cmd_list->pid == 0 && !sh->cmd_list->main_process)
	{
		prepare_pipe(sh);
		if (sh->cmd_list->infile)
			in_file(sh);
		if (sh->cmd_list->outfile)
			out_file(sh);
		if (sh->cmd_list->built_in)
			exec_built_in(sh);
		if (sh->cmd_list->cmd_arr)
			execute(sh);
	}
	// Main process
	sh->cmd_list = sh->cmd_list->start;
	temp_cmd = sh->cmd_list;
	while (temp_cmd)
	{
		if (temp_cmd->main_process) // no estoy seguro de si esto se tiene que hacer asi
		{
			if (sh->cmd_list->infile)
				in_file(sh);
			if (sh->cmd_list->outfile)
				out_file(sh);
			prepare_pipe(sh);
			exec_built_in(sh);
		}
		temp_cmd = temp_cmd->next;
	}
	sh->cmd_list = sh->cmd_list->start;
	temp_cmd = sh->cmd_list;
	pipe_cleaner(sh);
	temp_cmd = sh->cmd_list->start;
	while (temp_cmd)
	{
		waitpid(temp_cmd->pid, &sh->last_command, 0);
		//printf("%i\n", sh->last_comand);
		temp_cmd = temp_cmd->next;
	}
}
