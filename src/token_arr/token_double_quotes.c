/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:38:02 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_inside_quotes(t_token_arr_args *args, t_sh *sh)
{
	size_t	start;

	start = args->i;
	while (!is_in_set(args->str[args->i], "\'\"") && args->str[args->i])
	{
		if (args->str[args->i] == '$')
		{
			while (!is_in_set(args->str[args->i], "\'\" "))
				args->i++;
			break ;
		}
		skip_escaped(args, sh);
		args->i++;
	}
	if (args->token_arr)
	{
		args->token_arr[args->n_tokens]->is_in_quotes = true;
		if (args->str[start] == '$')
			args->token_arr[args->n_tokens]->is_variable = true;
		args->token_arr[args->n_tokens]->str = galloc(args->i - start + 1, sh);
		ft_strlcpy(args->token_arr[args->n_tokens]->str, \
			args->str + start, args->i - start + 1);
	}
	args->n_tokens++;
}

static void	copy_substr(t_token_arr_args *args, t_sh *sh, size_t start)
{
	t_token	**token_arr;
	char	*str;

	token_arr = args->token_arr;
	str = args->str;
	if (token_arr)
	{
		token_arr[args->n_tokens]->str = galloc(args->i - start + 1, sh);
		ft_strlcpy(token_arr[args->n_tokens]->str,
			str + start, args->i - start + 1);
		token_arr[args->n_tokens]->is_in_quotes = true;
	}
	args->n_tokens++;
	args->i++;
}

void	process_double_quotes(t_token_arr_args *args, t_sh *sh)
{
	size_t	start;

	args->i++;
	start = args->i;
	while (!is_in_set(args->str[args->i], "\"") && args->str[args->i])
	{
		skip_escaped(args, sh);
		if (args->str[args->i] && args->str[args->i] == '$')
		{
			if (args->i > start)
			{
				copy_substr(args, sh, start);
				args->i--;
			}
			process_inside_quotes(args, sh);
			start = args->i;
		}
		else
			args->i++;
	}
	if (args->i == args->arr_len)
		sh->syntax_error = true;
	if (start != args->i)
		copy_substr(args, sh, start);
}
