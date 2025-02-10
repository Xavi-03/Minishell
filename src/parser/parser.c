/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:35:55 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/10 19:28:11 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_builder(char *input, t_sh *sh)
{
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

int	manage_cmd_pipes(t_sh *sh)
{
	t_cmd	*cmd;
	int		fd_pipe[2];

	cmd = sh->cmd_list;
	cmd->out_pipe = 1;
	cmd = cmd_addnode(sh);
	if (pipe(fd_pipe) < 0)
	{
		ft_putstr_fd("Pipe Error\n", 2);
		terminate(EXIT_FAILURE, sh);
	}
	cmd->in_pipe = 1;
	cmd->fd_pipe = galloc(2 * sizeof(int), sh);
	cmd->fd_pipe[0] = fd_pipe[0];
	cmd->fd_pipe[1] = fd_pipe[1];
	return (1);
}

//command compare
int	cmd_parser(char *input, t_sh *sh)
{
	if (ft_strchr(input, '='))
		add_var(input, sh);
	else if (check_std_redir(input, sh))
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
	char		**var_arr;

	while (input_arr[++i])
	{
		if (input_arr[i][0] != '$')
		{
			cmd_parser(input_arr[i], sh);
			continue ;
		}
		var_arr = found_var(input_arr[i], sh);
		while (var_arr && *var_arr)
		{
			cmd_parser(*var_arr, sh);
			var_arr++;
		}
	}
	if (!input_arr[i])
		i = -1;
}

void	parser(t_sh *sh)
{
	char	**input_arr;

	sh->cmd_list = cmd_init(sh->cmd_list, sh);
	sh->cmd_list->start = sh->cmd_list;
	input_arr = sh->input_arr;
	find_cmd(input_arr, sh);
	if (!sh->cmd_list->cmd_arr)
		return ;
	if (sh->cmd_list->built_in || sh->cmd_list->cmd_arr)
		sh->cmd_list = fork_create(sh);
	if (sh->cmd_list->pid == -1 && !sh->cmd_list->main_process)
	{
		ft_putstr_fd("Fork Error\n", 2);
		terminate(EXIT_FAILURE, sh);
	}
	else if (sh->cmd_list->pid == 0 && !sh->cmd_list->main_process)
		subprocess_executer(sh);
	main_process_executer(sh);
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
