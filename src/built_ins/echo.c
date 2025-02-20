/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:38:53 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:19 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	echo_flag(t_cmd	*cmd, int *i)
{
	int	j;
	int	flag;

	flag = 0;
	while (ft_strncmp(cmd->cmd_arr[++(*i)], "-n", 2) == 0)
	{
		j = 0;
		while (cmd->cmd_arr[*i][++j])
		{
			if (cmd->cmd_arr[*i][j] != 'n')
				return (flag);
		}
		flag = 1;
	}
	return (flag);
}

void	echo(t_sh *sh)
{
	int		i;
	t_cmd	*cmd;
	int		flag;

	cmd = sh->cmd_list;
	i = 0;
	if (cmd->cmd_count == 1)
		return ((void)printf("\n"));
	flag = echo_flag(cmd, &i);
	while (cmd->cmd_arr[i] && cmd->cmd_arr[i + 1])
	{
		if (cmd->cmd_arr[i + 1][0] == ' ')
			printf("%s", cmd->cmd_arr[i++]);
		else
			printf("%s ", cmd->cmd_arr[i++]);
	}
	printf("%s", cmd->cmd_arr[i]);
	if (!flag)
		printf("\n");
}
