/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_recursive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:51:51 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/24 21:52:39 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	recursive_expand_var(t_token **token_arr, t_sh *sh)
{
	int		i;
	t_token	**new_token;

	i = -1;
	while (token_arr[++i])
	{
		if (token_arr[i]->is_variable)
		{
			new_token = found_var(token_arr[i]->str, sh);
			if (*new_token && (ft_strncmp (new_token[0]->str + 1, \
				token_arr[i]->str + 1, ft_strlen(token_arr[i]->str)) != 0))
				recursive_expand_var(new_token, sh);
		}
		else
			cmd_parser(token_arr[i], sh);
	}
}
