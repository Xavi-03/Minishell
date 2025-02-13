/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_skip_escaped.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/13 23:57:20 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_backslashes(t_cmd_arr_args *args, t_sh *sh)
{
	t_token	**cmd_arr;
	size_t	i;
	size_t	j;

	(void) sh;
	cmd_arr = args->cmd_arr;
	i = 0;
	while (cmd_arr[i])
	{
		j = 0;
		while (cmd_arr[i]->str[j])
		{
			if (cmd_arr[i]->str[j] == '\\' && cmd_arr[i]->str[j] \
				&& cmd_arr[i]->str[j + 1] && cmd_arr[i]->str[j + 1] != ' ')
			{
				ft_strlcpy(cmd_arr[i]->str + j, cmd_arr[i]->str + j + 1, \
					ft_strlen(cmd_arr[i]->str + j + 1));
			}
			j++;
		}
		i++;
	}
}

void	skip_escaped(t_cmd_arr_args *args, t_sh *sh)
{
	char	*str;

	(void) sh;
	str = args->str;
	if (str[args->i] == '\\' && str[args->i + 1] \
		&& str[args->i + 2])
		args->i += 2;
}
