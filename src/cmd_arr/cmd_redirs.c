/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/06 19:43:25 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	arrow_parser(char *str, size_t i)
{
	if ((str[i] == '>' && str[i] == '>')
		|| (str[i] == '<' && str[i] == '<'))
		i += 2;
	return (i);
}

void	process_redirs(t_cmd_arr_args *args, t_sh *sh)
{
	char	**cmd_arr;
	char	*str;
	size_t	start;

	start = args->i;
	cmd_arr = args->cmd_arr;
	str = args->str;

	args->i = arrow_parser(str, args->i);
	if (cmd_arr)
	{
		cmd_arr[args->n_substr] = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_substr], str + start, args->i - start + 1);
	}
	args->n_substr++;
	args->i++;
}
