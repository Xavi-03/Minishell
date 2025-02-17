/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:38:53 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 20:39:11 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(t_sh *sh)
{
	int		i;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	i = 0;
	if (cmd->cmd_count == 1)
	{
		printf("\n");
		return ;
	}
	i++;
	while (ft_strncmp(cmd->cmd_arr[i], "-n", 3) == 0)
		i++;
	while (cmd->cmd_arr[i] && cmd->cmd_arr[i + 1])
	{
		if (cmd->cmd_arr[i + 1][0] == ' ')
			printf("%s", cmd->cmd_arr[i++]);
		else
			printf("%s ", cmd->cmd_arr[i++]);
	}
	printf("%s", cmd->cmd_arr[i]);
	if (ft_strncmp(cmd->cmd_arr[1], "-n", 3) != 0)
		printf("\n");
}
