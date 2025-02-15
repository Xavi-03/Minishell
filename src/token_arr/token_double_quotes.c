/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/15 16:45:10 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_substr(t_token_arr_args *args, t_sh *sh, size_t start)
{
	t_token	**token_arr;
	char	*str;

	token_arr = args->token_arr;
	str = args->str;
	if (token_arr)
	{
		token_arr[args->n_tokens]->str = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(token_arr[args->n_tokens]->str,
			str + start, args->i - start + 1);
	}
	args->n_tokens++;
	args->i++;
}

void	process_double_quotes(t_token_arr_args *args, t_sh *sh)
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
	copy_substr(args, sh, start);
}
