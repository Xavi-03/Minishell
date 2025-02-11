/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_everything_else.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/11 17:14:51 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_everything_else(t_cmd_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;
	char	**cmd_arr;

	start = args->i;
	str = args->str;
	cmd_arr = args->cmd_arr;
	while (!is_in_set(str[args->i], "\'\"|>< ") && str[args->i])
	{
		skip_escaped(args, sh);
		if (str[args->i + 1] == '=' && is_in_set(str[args->i + 2], "\"\'"))
		{
			args->i += 3;
			while (!is_in_set(str[args->i], "\'\"") && str[args->i])
			{
				skip_escaped(args, sh);
				args->i++;
			}
		}
		args->i++;
	}
	if (cmd_arr)
	{
		cmd_arr[args->n_substr] = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_substr], str + start, args->i - start + 1);
	}
	args->n_substr++;
}
