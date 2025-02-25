/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:47:44 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/24 21:49:15 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	recursive_count_vars(t_token **token_arr, t_sh *sh, int *n_vars)
{
	int		i;
	t_token	**new_token;

	i = -1;
	while (token_arr && token_arr[++i])
	{
		if (token_arr[i]->is_variable)
		{
			new_token = found_var(token_arr[i]->str, sh);
			if (*new_token && (ft_strncmp (new_token[0]->str + 1, \
				token_arr[i]->str + 1, ft_strlen(token_arr[i]->str)) != 0))
				recursive_count_vars(new_token, sh, n_vars);
		}
		else
			(*n_vars)++;
	}
}

int	count_tokens(t_token **token_arr, t_sh *sh)
{
	int	i;
	int	n_vars;

	i = -1;
	n_vars = 0;
	while (token_arr[++i])
	{
		if (token_arr[i]->is_variable)
			recursive_count_vars(found_var(token_arr[i]->str, sh), sh, &n_vars);
		else
			n_vars++;
	}
	return (i + n_vars);
}
