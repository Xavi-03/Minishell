/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:22:48 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/02/25 20:22:49 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_export(t_sh *sh)
{
	char	**cmd_arr;
	int		i;

	i = 0;
	cmd_arr = sh->cmd_list->cmd_arr;
	while (cmd_arr[++i])
	{
		if (ft_isdigit(cmd_arr[i][0]))
		{
			ft_putstr_fd("Syntax Error\n", 2);
			return (1);
		}
	}
	return (0);
}

int	strlen_toc(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
