/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skip_escaped.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/15 16:14:15 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_backslashes(t_token_arr_args *args, t_sh *sh)
{
	t_token	**token_arr;
	size_t	i;
	size_t	j;

	(void) sh;
	token_arr = args->token_arr;
	i = 0;
	while (token_arr[i])
	{
		j = 0;
		while (token_arr[i]->str[j])
		{
			if (token_arr[i]->str[j] == '\\' && token_arr[i]->str[j] \
				&& token_arr[i]->str[j + 1] && token_arr[i]->str[j + 1] != ' ')
			{
				ft_strlcpy(token_arr[i]->str + j, token_arr[i]->str + j + 1, \
					ft_strlen(token_arr[i]->str + j + 1));
			}
			j++;
		}
		i++;
	}
}

void	skip_escaped(t_token_arr_args *args, t_sh *sh)
{
	char	*str;

	(void) sh;
	str = args->str;
	if (str[args->i] == '\\' && str[args->i + 1] \
		&& str[args->i + 2])
		args->i += 2;
}
