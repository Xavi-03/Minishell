/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:35:55 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/15 17:47:03 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_builder(char *input, t_sh *sh)
{
	t_cmd	*cmd;
	char	*exec_path;

	cmd = sh->cmd_list;
	find_built_in(input, sh);
	if (sh->cmd_list->cmd_count == 0)
	{
		cmd->cmd_arr = galloc(10 * sizeof(char *), sh);
		exec_path = get_path(input, sh);
		if (cmd->built_in || !exec_path)
			cmd->cmd_arr[cmd->cmd_count] = ft_strdup(input);
		else
			cmd->cmd_arr[cmd->cmd_count] = exec_path;
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

void	find_cmd(t_token **token_arr, t_sh *sh)
{
	static int	i = -1;
	t_token		**var_arr;

	while (token_arr[++i])
	{
		if (!token_arr[i]->is_variable)
		{
			cmd_parser(token_arr[i]->str, sh);
			continue ;
		}
		var_arr = found_var(token_arr[i]->str, sh);
		while (var_arr && *var_arr)
		{
			cmd_parser((*var_arr)->str, sh);
			var_arr++;
		}
	}
	if (!token_arr[i])
		i = -1;
}

void	parser(t_sh *sh)
{
	t_token	**token_arr;

	sh->cmd_list = cmd_init(sh->cmd_list, sh);
	sh->cmd_list->start = sh->cmd_list;
	token_arr = sh->token_arr;
	find_cmd(token_arr, sh);
	if (!sh->cmd_list->cmd_arr)
	{
		check_redirs(sh);
		return ;
	}
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
