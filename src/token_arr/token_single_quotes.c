/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_single_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 20:43:31 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_single_quotes(t_token_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;
	t_token	**token_arr;

	args->i++;
	start = args->i;
	str = args->str;
	token_arr = args->token_arr;
	while (!is_in_set(str[args->i], "\'") && str[args->i])
	{
		skip_escaped(args, sh);
		args->i++;
	}
	if (token_arr)
	{
		token_arr[args->n_tokens]->is_in_quotes = true;
		token_arr[args->n_tokens]->str = galloc(args->i - start + 1, sh);
		ft_strlcpy(token_arr[args->n_tokens]->str, \
			str + start, args->i - start + 1);
	}
	args->n_tokens++;
	args->i++;
}
