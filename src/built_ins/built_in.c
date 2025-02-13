/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:18:02 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/13 22:58:48 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_built_in(char *input, char *cmd)
{
	if (ft_strncmp(input, cmd, ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

static void	set_main_process(t_sh *sh)
{
	sh->cmd_list->main_process = 1;
}

void	find_built_in(char *input, t_sh *sh)
{
	if (is_built_in(input, "echo"))
		;
	else if (is_built_in(input, "cd"))
		set_main_process(sh);
	else if (is_built_in(input, "pwd"))
		;
	else if (is_built_in(input, "export"))
		set_main_process(sh);
	else if (is_built_in(input, "unset"))
		set_main_process(sh);
	else if (is_built_in(input, "env"))
		;
	else if (is_built_in(input, "exit"))
		set_main_process(sh);
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
		cd(sh);
	else if (is_built_in(cmd, "pwd"))
		printf("pwd\n");//TODO
	else if (is_built_in(cmd, "export"))
		export(sh);
	else if (is_built_in(cmd, "unset"))
		unset(sh);
	else if (is_built_in(cmd, "env"))
		print_env(sh);
	else if (is_built_in(cmd, "exit"))
		terminate(EXIT_SUCCESS, sh);
	else
		return (1);
	return (0);
}

void	echo(t_sh *sh)
{
	int		i;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	i = 0;
	if (cmd->cmd_count == 1)
		printf("\n");
	if (ft_strncmp(cmd->cmd_arr[1], "-n", 3) == 0)
		i++;
	i++;
	while (cmd->cmd_arr[i])
		printf("%s", cmd->cmd_arr[i++]);
	if (ft_strncmp(cmd->cmd_arr[1], "-n", 3) != 0)
		printf("\n");
}
