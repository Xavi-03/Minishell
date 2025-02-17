/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_everything_else.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 20:47:04 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_after_equal(t_token_arr_args *args, t_sh *sh)
{
	args->i += 3;
	while (!is_in_set(args->str[args->i], "\'\"") && args->str[args->i])
	{
		skip_escaped(args, sh);
		args->i++;
	}
}

void	process_everything_else(t_token_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;
	t_token	**token_arr;

	start = args->i;
	str = args->str;
	token_arr = args->token_arr;
	while (!is_in_set(str[args->i], "\'\"|>< ") && str[args->i])
	{
		skip_escaped(args, sh);
		if (str[args->i + 1] == '=' && is_in_set(str[args->i + 2], "\"\'"))
			process_after_equal(args, sh);
		args->i++;
	}
	if (token_arr)
	{
		if (str[start] == '$')
			token_arr[args->n_tokens]->is_variable = true;
		token_arr[args->n_tokens]->str = galloc(args->i - start + 1, sh);
		ft_strlcpy(token_arr[args->n_tokens]->str, \
			str + start, args->i - start + 1);
	}
	args->n_tokens++;
}
