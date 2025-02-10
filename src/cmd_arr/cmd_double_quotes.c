/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_double_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/10 22:00:20 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_substr(t_cmd_arr_args *args, t_sh *sh, size_t start)
{
	char	**cmd_arr;
	char	*str;

	cmd_arr = args->cmd_arr;
	str = args->str;
	if (cmd_arr)
	{
		cmd_arr[args->n_substr] = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_substr], str + start, args->i - start + 1);
	}
	args->n_substr++;
	args->i++;
}

void	process_double_quotes(t_cmd_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;

	args->i++;
	start = args->i;
	str = args->str;
	while (!is_in_set(str[args->i], "\"|><") && str[args->i])
	{
		if (str[args->i] && str[args->i] == '$')
		{
			if (args->i > start)
			{
				copy_substr(args, sh, start);
				args->i--;
			}
			process_everything_else(args, sh);
			start = args->i;
		}
		args->i++;
	}
	if (str[start] != '\"')
		copy_substr(args, sh, start);
}
