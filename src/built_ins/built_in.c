/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:18:02 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:14 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_built_in(char *input, char *cmd)
{
	if (ft_strncmp(input, cmd, ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

void	find_built_in(char *input, t_sh *sh)
{
	if (is_built_in(input, "echo"))
		;
	else if (is_built_in(input, "cd"))
		sh->cmd_list->main_process = 1;
	else if (is_built_in(input, "pwd"))
		;
	else if (is_built_in(input, "export"))
		sh->cmd_list->main_process = 1;
	else if (is_built_in(input, "unset"))
		sh->cmd_list->main_process = 1;
	else if (is_built_in(input, "env"))
		;
	else if (is_built_in(input, "exit"))
		sh->cmd_list->main_process = 1;
	else
		return ;
	sh->cmd_list->built_in = 1;
}

int	exec_built_in(t_sh *sh)
{
	char	*cmd;

	cmd = sh->cmd_list->cmd_arr[0];
	if (is_built_in(cmd, "echo"))
		echo(sh);
	else if (is_built_in(cmd, "cd"))
		return (cd(sh));
	else if (is_built_in(cmd, "pwd"))
		pwd(sh);
	else if (is_built_in(cmd, "export"))
	{
		if (check_export(sh))
			return (1);
		export(sh);
	}
	else if (is_built_in(cmd, "unset"))
		unset(sh);
	else if (is_built_in(cmd, "env"))
		print_env(sh);
	else if (is_built_in(cmd, "exit"))
		exit_builtin(sh);
	else
		return (1);
	return (0);
}

void	exit_builtin(t_sh *sh)
{
	char	**cmd_arr;
	int		n_cmd;

	cmd_arr = sh->cmd_list->cmd_arr;
	n_cmd = sh->cmd_list->cmd_count;
	if (n_cmd == 1)
		terminate(0, sh);
	if (n_cmd > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		sh->last_command = 1;
		return ;
	}
	if (parser_int(cmd_arr[1], sh))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		terminate(2, sh);
	}
	terminate(sh->exit_value, sh);
}

void	print_env(t_sh *sh)
{
	char	**env_ptr;

	if (!sh->env)
		return ;
	env_ptr = sh->env;
	while (*env_ptr)
		printf("%s\n", *env_ptr++);
}
