/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:35:55 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/24 21:51:02 by pohernan         ###   ########.fr       */
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
		cmd->cmd_arr = galloc((count_tokens(sh->token_arr, sh) + 3) \
			* sizeof(char *), 1, sh);
		exec_path = get_path(input, sh);
		if (cmd->built_in || !exec_path)
			cmd->cmd_arr[cmd->cmd_count] = ft_strdup(input);
		else
			cmd->cmd_arr[cmd->cmd_count] = ft_strdup(exec_path);
		add_galloc(cmd->cmd_arr[cmd->cmd_count], 1, sh);
	}
	else
	{
		cmd->cmd_arr[cmd->cmd_count] = ft_strdup(input);
		add_galloc(cmd->cmd_arr[cmd->cmd_count], 1, sh);
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
	cmd->fd_pipe = galloc(2 * sizeof(int), 0, sh);
	cmd->fd_pipe[0] = fd_pipe[0];
	cmd->fd_pipe[1] = fd_pipe[1];
	return (1);
}

int	cmd_parser(t_token *token, t_sh *sh)
{
	if (ft_strchr(token->str, '='))
	{
		add_var(token->str, sh);
		if (sh->cmd_list->cmd_arr && ft_strncmp(sh->cmd_list->cmd_arr[0], \
			"export", ft_strlen(sh->cmd_list->cmd_arr[0])) == 0)
			command_builder(token->str, sh);
	}
	else if (check_std_redir(token->str, sh) && !token->is_in_quotes)
		check_in_out_file(token->str, sh);
	else if (ft_strncmp(token->str, "|", 2) == 0 && !token->is_in_quotes)
		manage_cmd_pipes(sh);
	else
		command_builder(token->str, sh);
	return (0);
}

void	find_cmd(t_token **token_arr, t_sh *sh)
{
	int		i;
	t_token	**new_token;

	i = -1;
	while (token_arr[++i])
	{
		if (token_arr[i]->is_variable)
		{
			new_token = found_var(token_arr[i]->str, sh);
			if (*new_token && (ft_strncmp (new_token[0]->str + 1, \
				token_arr[i]->str + 1, ft_strlen(token_arr[i]->str)) != 0))
				recursive_expand_var(new_token, sh);
		}
		else
			cmd_parser(token_arr[i], sh);
	}
}

void	parser(t_sh *sh)
{
	sh->cmd_list = cmd_init(sh->cmd_list, sh);
	sh->cmd_list->start = sh->cmd_list;
	find_cmd(sh->token_arr, sh);
	if (!sh->cmd_list->cmd_arr || sh->syntax_error)
	{
		if (!sh->token_arr[0] || (sh->token_arr[0]->str
				&& ft_strchr(sh->token_arr[0]->str, '=')))
			return ;
		if (!sh->cmd_list->cmd_arr && !sh->syntax_error && !check_redirs(sh))
			return ;
		sh->syntax_error = false;
		sh->last_command = 1;
		ft_putstr_fd("Syntax Error\n", 2);
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
