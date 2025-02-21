/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:38:07 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	arrow_parser(char *str, size_t i)
{
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		i += 2;
	else if ((str[i] == '>' && str[i + 1] != '>')
		|| (str[i] == '<' && str[i + 1] != '<'))
		i++;
	else if ((str[i] == '|' && str[i + 1] != '|')
		|| (str[i] == '|' && str[i + 1] != '|'))
		i++;
	return (i);
}

void	process_redirs(t_token_arr_args *args, t_sh *sh)
{
	t_token	**token_arr;
	char	*str;
	size_t	start;

	start = args->i;
	token_arr = args->token_arr;
	str = args->str;
	args->i = arrow_parser(str, args->i);
	if (token_arr)
	{
		token_arr[args->n_tokens]->str = galloc(args->i - start + 1, 1, sh);
		ft_strlcpy(token_arr[args->n_tokens]->str, \
			str + start, args->i - start + 1);
	}
	args->n_tokens++;
}
