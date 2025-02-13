/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_single_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/13 23:40:25 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_single_quotes(t_cmd_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;
	t_token	**cmd_arr;

	start = args->i;
	args->i++;
	str = args->str;
	cmd_arr = args->cmd_arr;
	while (!is_in_set(str[args->i], "\'") && str[args->i])
	{
		skip_escaped(args, sh);
		args->i++;
	}
	if (cmd_arr)
	{
		cmd_arr[args->n_tokens]->str = (char *)galloc(args->i - start + 2, sh);
		ft_strlcpy(cmd_arr[args->n_tokens]->str, str + start, args->i - start + 2);
	}
	args->n_tokens++;
	args->i++;
}
