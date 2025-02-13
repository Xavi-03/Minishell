/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_double_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/13 23:40:10 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_substr(t_cmd_arr_args *args, t_sh *sh, size_t start)
{
	t_token	**cmd_arr;
	char	*str;

	cmd_arr = args->cmd_arr;
	str = args->str;
	if (cmd_arr)
	{
		cmd_arr[args->n_tokens]->str = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_tokens]->str, str + start, args->i - start + 1);
	}
	args->n_tokens++;
	args->i++;
}

void	process_double_quotes(t_cmd_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;

	start = args->i;
	args->i++;
	str = args->str;
	while (!is_in_set(str[args->i], "\"|><") && str[args->i])
	{
		skip_escaped(args, sh);
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
